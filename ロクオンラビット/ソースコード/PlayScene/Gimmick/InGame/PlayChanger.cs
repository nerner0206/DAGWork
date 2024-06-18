using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayChanger : MonoBehaviour
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;

    public void Change(bool flag)
    {
        m_animator.SetBool("Change", flag);
    }
}
