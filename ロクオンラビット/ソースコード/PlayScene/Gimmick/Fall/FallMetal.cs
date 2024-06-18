using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallMetal : Fall
{
    [SerializeField, Tooltip("音を拾えるようにする")]
    private PlayGimmickSE m_playGimmickSE;
    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;

    [SerializeField, Tooltip("子供のアニメーター")]
    private Animator[] m_animators;

    public void Start()
    {
        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();
    }

    public override void ActionFall()
    {
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        m_audioSource.Play();

        m_animators[0].SetTrigger("Melt");
        m_animators[1].SetTrigger("Melt");
    }
}
