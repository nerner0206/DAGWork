using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayFireObj : PlayGimmick
{
    [SerializeField, Tooltip("炎の体力")]
    private int m_fireHp = 3;
    [SerializeField, Tooltip("時間")]
    private float m_coolTime = 1f;

    [SerializeField, Tooltip("音を渡すギミック")]
    private PlayGimmickSE m_playGimmickSE;

    //  計算用の体力
    private int m_fh = 0;
    //  デフォルトのサイズ
    private Vector3 m_defScale = Vector3.one;

    //  時間
    private float m_timer;

    //  音が接触
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  触れた音の種類の取得
        m_hitSoundKind = kind;

        //  ※水の音では当たった時の処理をUpdate内に書くのがデフォルトとする
    }

    //  音が離れた
    public override void SoundNot()
    {
        base.SoundNot();
    }

    //  リセット
    public override void GimmickReset()
    {
        //  初期体力の設定
        m_fh = m_fireHp;

        //  クールタイムの設定
        m_timer = m_coolTime;

        //  初期化
        m_playGimmickSE.Init();
        //  拾える状態にする
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  大きさ更新
        gameObject.transform.localScale = m_defScale;
    }

    //  初期化
    public override void Init()
    {
        m_fh = m_fireHp;

        m_timer = m_coolTime;
        //  初期サイズを取得
        m_defScale = gameObject.transform.localScale;

        //  初期化
        m_playGimmickSE.Init();
        //  拾える状態にする
        m_playGimmickSE.OnGimmickSE(m_soundKind);
    }

    //  水の音が接触
    public virtual void HitWater()
    {
        if (m_timer > 0f)
        {
            //  時間を減らす
            m_timer -= Time.deltaTime;
            //  処理終了
            return;
        }

        //  炎の体力を減らす
        m_fh -= 1;
        //  体力が０になったら削除する
        if(m_fh <= 0)
        {
            //  削除
            gameObject.SetActive(false);
            //  処理終了
            return;
        }

        //  時間をリセット
        m_timer = m_coolTime;
        //  大きさを変更する
        Vector3 s = Vector3.Lerp(Vector3.zero, m_defScale, (float)m_fh / (float)m_fireHp);
        //  大きさ更新
        gameObject.transform.localScale = s;
    }
}
