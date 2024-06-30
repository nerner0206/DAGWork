using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
[RequireComponent(typeof(Rigidbody2D))]
public class WoodBox : PlayWoodObj
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;
    [SerializeField, Tooltip("物理")]
    private Rigidbody2D m_rb;
    [SerializeField, Tooltip("音を拾える範囲")]
    private MomentGimmickSE m_gimmickSE;
    [SerializeField, Tooltip("破壊済み")]
    private bool m_isBreak = false;
    [SerializeField, Tooltip("レイを飛ばす位置")]
    private Transform m_rayPos;
    
    [SerializeField, Tooltip("音の素材")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("破壊基準")]
    private float m_breakPower;

    [SerializeField, Tooltip("木箱破壊エフェクト")]
    private ParticleSystem m_breakEffect;

    //  破壊状態の取得・設定
    public bool GetSetIsBreak
    {
        get { return m_isBreak; }
        set { m_isBreak = value; }
    }

    public override void Init()
    {
        //  音を効果音に変える
        m_audioSource.clip = m_audioClips[0];

        //  初期化
        m_gimmickSE.Init();
        //  消す
        m_gimmickSE.OffGimmickSE();

        if (!m_isBreak) return;
        //  最初から壊れている
        //  通常再生
        Breaking();
    }

    //  音がヒット
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  デフォルトを使用
        base.SoundHit(kind, pitch, audioClip);
    }
    //  破壊音で壊す処理
    public override void HitBreak(float pitch) 
    {
        //  逆再生か判定する&&既に壊れている
        if(pitch < 0 && m_isBreak)
        {
            //  直す
            m_isBreak = false;
            //  修復アニメーションを再生
            m_animator.SetBool("Break", m_isBreak);

            //  レイヤーを切り替える
            int layer = LayerMask.NameToLayer("Box");
            gameObject.layer = layer;

            //  音を効果音に変える
            m_audioSource.clip = m_audioClips[0];
            //  音を拾えなくする
            m_gimmickSE.OffGimmickSE();

            //  処理終了
            return;
        }
        else if(pitch > 0 && !m_isBreak)
        {
            //  通常再生
            Breaking();
        }
        
    }

    //  破壊
    private void Breaking()
    {
        //  壊す
        m_isBreak = true;
        //  破壊アニメーションを再生
        m_animator.SetBool("Break", m_isBreak);

        //  レイヤーを切り替える
        int layer = LayerMask.NameToLayer("Breaking"); ;
        gameObject.layer = layer;

        //  音を破壊音に変える
        m_audioSource.clip = m_audioClips[1];
        //  鳴らす
        m_audioSource.Play();
        m_breakEffect.Play();
        //  破壊音の発生
        m_gimmickSE.OnGimmickSE(m_soundKind, 0.2f);

        //  箱の場合
        m_rb.constraints = RigidbodyConstraints2D.FreezePositionX
            | RigidbodyConstraints2D.FreezeRotation;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        //  衝突時の力を取得
        float hitPower = collision.contacts[0].normalImpulse;
        //  衝突の力が小さければ処理しない
        if (hitPower < m_breakPower || m_isBreak) return;

        //  破壊
        Breaking();
    }
    private void OnCollisionExit2D(Collision2D collision)
    {
        //  離れたオブジェクトがベルトコンベアを持っている
        if(collision.gameObject.TryGetComponent(out BeltConveyor belt))
        {
            //  レイを下に飛ばす
            int layer = LayerMask.GetMask("Belt");
            //  Rayを飛ばす
            RaycastHit2D hitObj = Physics2D.CircleCast(m_rayPos.position, 0.5f, Vector2.zero, 0.0f, layer);
            //  ベルトコンベアがある
            if (hitObj.collider != null)
            {
                //  動いているなら処理しない
                if (hitObj.collider.GetComponent<PlayBeltObj>().GetSetIsMove) return;
                //  箱の場合
                m_rb.constraints = RigidbodyConstraints2D.FreezePositionX
                    | RigidbodyConstraints2D.FreezeRotation;
            }
            else
            {
                //  箱の場合
                m_rb.constraints = RigidbodyConstraints2D.FreezePositionX
                    | RigidbodyConstraints2D.FreezeRotation;
            }
        }
    }
}
