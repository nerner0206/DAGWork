using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class GlassWall : PlayGlassObj
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;
    [SerializeField, Tooltip("破壊済み")]
    private bool m_isBreak = false;
    [SerializeField, Tooltip("音を拾える範囲")]
    private MomentGimmickSE m_gimmickSE;

    [SerializeField, Tooltip("ガラス")]
    private GameObject m_glass;
    [SerializeField, Tooltip("ガラス破片")]
    private GameObject m_partR;
    [SerializeField, Tooltip("ガラス破片")]
    private GameObject m_partL;

    [SerializeField, Tooltip("音の素材")]
    private AudioClip[] m_audioClips;

    [SerializeField, Tooltip("ガラス破片")]
    private ParticleSystem m_glassEffect;

    public override void Init()
    {
        //  音を効果音に変える
        m_audioSource.clip = m_audioClips[0];

        //  初期化
        m_gimmickSE.Init();
        //  消す
        m_gimmickSE.OffGimmickSE();

        if (!m_isBreak) return;
        Breaking();
    }

    //  破壊音で壊す処理
    public override void HitBreak(float pitch)
    {
        //  逆再生か判定する&&既に壊れている
        if (pitch < 0 && m_isBreak)
        {
            //  直す
            m_isBreak = false;
            //  修復アニメーションを再生
            //animator.SetBool("Break", isBreak);

            m_glass.SetActive(true);

            m_partR.SetActive(false);
            m_partL.SetActive(false);

            //  レイヤーを切り替える
            int layer = LayerMask.NameToLayer("Ground");
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
        //animator.SetBool("Break", isBreak);

        m_glass.SetActive(false);

        m_partR.SetActive(true);
        m_partL.SetActive(true);

        //  レイヤーを切り替える
        int layer = LayerMask.NameToLayer("Breaking"); ;
        gameObject.layer = layer;

        //  音を破壊音に変える
        m_audioSource.clip = m_audioClips[1];

        m_glassEffect.Play();

        //  鳴らす
        m_audioSource.Play();

        //  破壊音の発生
        m_gimmickSE.OnGimmickSE(m_soundKind, 0.1f);
    }
}
