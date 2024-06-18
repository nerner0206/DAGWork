using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class WoodBoxCreator : PlayElecObj
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;

    [SerializeField, Tooltip("生成する箱のプレハブ")]
    private GameObject m_boxPrefab;

    [Header("生成情報")]

    [SerializeField, Tooltip("生成する箱の上限")]
    private int m_maxNum = 1;
    [SerializeField, Tooltip("同時に存在できる箱の数")]
    private int m_sameNum = 1;
    [SerializeField, Tooltip("生成時間の間隔")]
    private float m_createTime = 5.0f;
    [SerializeField, Tooltip("生成位置")]
    private Transform m_createPos;
    [SerializeField, Tooltip("プレイヤーの位置")]
    private Transform m_player;

    //  生成した箱の数
    private int m_createNum;
    //  存在している箱の数
    private int m_nowNum;
    //  タイマー
    private float m_timer;
    //  生成したオブジェクトを格納する配列
    private WoodBox[] m_boxes;
    //  箱のAudioSourcs
    private AudioSource[] m_boxesAudio;

    //  壊れたオブジェクトを格納する配列
    private GameObject breakboxes;

    //  初期化
    public override void Init()
    {
        //  生成数
        m_createNum = 0;
        m_nowNum = 0;
        //  時間
        m_timer = 0f;
        //  初期化
        m_boxes = new WoodBox[m_sameNum];
        m_boxesAudio = new AudioSource[m_sameNum];

        breakboxes = null;
    }

    //  更新
    private void Update()
    {
        for (int i = 0; i < m_nowNum; i++)
        {
            //  箱が無かったら処理しない
            if (m_boxes[i] == null) continue;

            //  箱が壊れていない
            if (!m_boxes[i].GetSetIsBreak) continue;

            if (breakboxes != null) Destroy(breakboxes);

            breakboxes = m_boxes[i].gameObject;

            //  破壊されている
            for (int j = i;j < m_nowNum - 1;j++)
            {
                //  上書き
                m_boxes[j] = m_boxes[j + 1];
                m_boxesAudio[j] = m_boxesAudio[j + 1];
            }
            //  最後の要素をnullにする
            m_boxes[m_nowNum - 1] = null;
            m_boxesAudio[m_nowNum - 1] = null;
            //  減らす
            m_nowNum--;
        }

        //  音量調節
        for (int i = 0; i < m_nowNum; i++)
        {
            //  箱が無かったら処理しない
            if (m_boxes[i] == null) continue;

            //  ギミック音とプレイヤーの距離を測る
            float distance = Vector3.Distance(m_player.position, m_boxes[i].gameObject.transform.position);
            //  最大距離との割合
            float vol = 1 - (distance / 10);
            //  音量がマイナスになったら０に戻す
            if (vol < 0) vol = 0f;
            //  音量を設定
            m_boxesAudio[i].volume = vol;
        }

        //  通電していなかったら処理しない
        if (!m_hitElec) return;

        //  生成数が最大数を超えたら処理しない || 生成数が-1なら無限に生成する
        if (m_maxNum != -1)
        {
            if (m_createNum >= m_maxNum) return;
        }

        //  時間を増やす
        m_timer += Time.deltaTime;

        //  存在している箱の数が上限を超えている
        if (m_nowNum >= m_sameNum) return;
        //  生成時間より小さい
        if (m_timer < m_createTime) return;

        //  生成する処理
        Create();
    }

    //  生成する処理
    private void Create()
    {
        m_animator.SetTrigger("Create");

        //  生成する
        GameObject box = Instantiate(m_boxPrefab,
            m_createPos.position,
            Quaternion.identity);

        //  箱のサイズを生成器に合わせる
        box.transform.localScale *= gameObject.transform.localScale.x;
        //  生成位置の調整

        //  格納する
        m_boxes[m_nowNum] = box.GetComponent<WoodBox>();
        m_boxesAudio[m_nowNum] = box.GetComponent<AudioSource>();

        //  タイマーを初期化
        m_timer = 0f;
        //  生成した数を初期化
        m_createNum++;
        m_nowNum++;
    }

    //  リセット
    public override void GimmickReset()
    {
        //  生成数
        m_createNum = 0;
        m_nowNum = 0;
        //  時間
        m_timer = 0f;
        //  初期化
        for (int i = 0; i < m_sameNum; i++) 
        {
            if (m_boxes[i] != null) Destroy(m_boxes[i].gameObject);
            m_boxesAudio[i] = null;
        }

        //  初期化
        m_boxes = new WoodBox[m_sameNum];

        breakboxes = null;
    }

    //  電気の接触
    public override void HitElec()
    {
        base.HitElec();
    }
}
