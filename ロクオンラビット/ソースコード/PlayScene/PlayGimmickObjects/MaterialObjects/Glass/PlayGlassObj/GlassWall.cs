using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class GlassWall : PlayGlassObj
{
    [SerializeField, Tooltip("ƒAƒjƒ[ƒ^[")]
    private Animator m_animator;
    [SerializeField, Tooltip("”j‰óÏ‚İ")]
    private bool m_isBreak = false;
    [SerializeField, Tooltip("‰¹‚ğE‚¦‚é”ÍˆÍ")]
    private MomentGimmickSE m_gimmickSE;

    [SerializeField, Tooltip("ƒKƒ‰ƒX")]
    private GameObject m_glass;
    [SerializeField, Tooltip("ƒKƒ‰ƒX”j•Ğ")]
    private GameObject m_partR;
    [SerializeField, Tooltip("ƒKƒ‰ƒX”j•Ğ")]
    private GameObject m_partL;

    [SerializeField, Tooltip("‰¹‚Ì‘fŞ")]
    private AudioClip[] m_audioClips;

    [SerializeField, Tooltip("ƒKƒ‰ƒX”j•Ğ")]
    private ParticleSystem m_glassEffect;

    public override void Init()
    {
        //  ‰¹‚ğŒø‰Ê‰¹‚É•Ï‚¦‚é
        m_audioSource.clip = m_audioClips[0];

        //  ‰Šú‰»
        m_gimmickSE.Init();
        //  Á‚·
        m_gimmickSE.OffGimmickSE();

        if (!m_isBreak) return;
        Breaking();
    }

    //  ”j‰ó‰¹‚Å‰ó‚·ˆ—
    public override void HitBreak(float pitch)
    {
        //  ‹tÄ¶‚©”»’è‚·‚é&&Šù‚É‰ó‚ê‚Ä‚¢‚é
        if (pitch < 0 && m_isBreak)
        {
            //  ’¼‚·
            m_isBreak = false;
            //  C•œƒAƒjƒ[ƒVƒ‡ƒ“‚ğÄ¶
            //animator.SetBool("Break", isBreak);

            m_glass.SetActive(true);

            m_partR.SetActive(false);
            m_partL.SetActive(false);

            //  ƒŒƒCƒ„[‚ğØ‚è‘Ö‚¦‚é
            int layer = LayerMask.NameToLayer("Ground");
            gameObject.layer = layer;

            //  ‰¹‚ğŒø‰Ê‰¹‚É•Ï‚¦‚é
            m_audioSource.clip = m_audioClips[0];
            //  ‰¹‚ğE‚¦‚È‚­‚·‚é
            m_gimmickSE.OffGimmickSE();

            //  ˆ—I—¹
            return;
        }
        else if(pitch > 0 && !m_isBreak)
        {
            //  ’ÊíÄ¶
            Breaking();
        }
    }

    //  ”j‰ó
    private void Breaking()
    {
        //  ‰ó‚·
        m_isBreak = true;
        //  ”j‰óƒAƒjƒ[ƒVƒ‡ƒ“‚ğÄ¶
        //animator.SetBool("Break", isBreak);

        m_glass.SetActive(false);

        m_partR.SetActive(true);
        m_partL.SetActive(true);

        //  ƒŒƒCƒ„[‚ğØ‚è‘Ö‚¦‚é
        int layer = LayerMask.NameToLayer("Breaking"); ;
        gameObject.layer = layer;

        //  ‰¹‚ğ”j‰ó‰¹‚É•Ï‚¦‚é
        m_audioSource.clip = m_audioClips[1];

        m_glassEffect.Play();

        //  –Â‚ç‚·
        m_audioSource.Play();

        //  ”j‰ó‰¹‚Ì”­¶
        m_gimmickSE.OnGimmickSE(m_soundKind, 0.1f);
    }
}
