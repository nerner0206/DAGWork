using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class PlayElevatorObj : PlayGimmick
{
    [SerializeField, Tooltip("乗る部分")]
    private Transform m_ground;

    [SerializeField, Tooltip("上昇位置")]
    private Transform m_top;
    [SerializeField, Tooltip("下降位置")]
    private Transform m_bottom;

    [SerializeField, Tooltip("最初から稼働しているか")]
    private bool m_isMove = false;

    [SerializeField, Tooltip("最初から上昇するか")]
    private bool m_isUp = true;

    [SerializeField, Tooltip("移動速度")]
    private float m_moveSpeed = 1.0f;

    [SerializeField, Tooltip("音を拾うスクリプト")]
    private PlayGimmickSE m_playGimmickSE;

    //  移動方向の計算
    private Vector3 m_dir;

    //  アニメーター
    private Animator m_animator;
    //  初期状態
    private bool m_startMove = false;
    //  デフォルト座標
    private Vector3 m_defPos;

    //  初期化
    public override void Init()
    {
        m_animator = GetComponent<Animator>();

        m_startMove = m_isMove;

        m_defPos = gameObject.transform.position;

        //  移動方向
        if (m_isUp) m_dir = (m_top.position - m_ground.position).normalized;
        else m_dir = (m_bottom.position - m_ground.position).normalized;

        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        if (m_isMove) ElevatorMove();
    }

    public override void GimmickReset()
    {
        gameObject.transform.position = m_defPos;

        if (m_startMove) ElevatorMove();
        else ElevatorStop();
    }

    //  ヒットしたら
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  音の種類を取得
        m_hitSoundKind = kind;

        switch (m_hitSoundKind) 
        {
            //  モーター音
            case SoundKind.Motor:
                //  音を取得
                m_audioSource.pitch = pitch;
                //  ヒット処理
                //  既に稼働済み
                if (m_isMove) ElevatorStop();
                else ElevatorMove();
                break;
            //  処理しない
            default:
                return;
        }
    }

    //  エレベーターを止める
    private void ElevatorMove()
    {
        //  動かす
        m_isMove = true;
        //  アニメーターの再生
        m_animator.SetBool("Move", m_isMove);

        //  音を取れるようにする
        m_playGimmickSE.OnGimmickSE(m_soundKind);

        //  鳴らす
        m_audioSource.Play();
    }
    //  エレベーターを稼働する
    private void ElevatorStop()
    {
        //  止める
        m_isMove = false;
        //  アニメーターの再生
        m_animator.SetBool("Move", m_isMove);

        //  音を取れないようにする
        m_playGimmickSE.OffGimmickSE();

        //  音を止める
        m_audioSource.Stop();
    }

    public override void SwichOn()
    {
        ElevatorMove();
    }
    public override void SwichOff()
    {
        ElevatorStop();
    }

    //  更新処理
    private void Update()
    {
        //  処理しない
        if (!m_isMove) return;

        //  上昇中
        if (m_isUp)
        {
            
            //  上昇する
            m_ground.position += m_dir * m_moveSpeed * Time.deltaTime;

            //  上昇を終えたら
            if(m_ground.position.y >= m_top.position.y)
            {
                //  下降する
                m_isUp = false;
                //移動方向を変える
                m_dir = (m_bottom.position - m_ground.position).normalized;
                
            }
        }
        //  下降中
        else
        {
            //  下降する
            m_ground.position += m_dir * m_moveSpeed * Time.deltaTime;

            //  上昇を終えたら
            if (m_ground.position.y <= m_bottom.position.y)
            {
                //  下降する
                m_isUp = true;
                //移動方向を変える
                m_dir = (m_top.position - m_ground.position).normalized;
                
            }
        }
    }
}
