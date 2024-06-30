using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class Warp : MonoBehaviour
{
    [SerializeField, Tooltip("������̃��[�v��")]
    private Warp m_warp;

    //  ���[�v���Ă�����
    private bool m_warping;

    //  ���[�v�̎󂯓n��
    public bool GetSetWarping
    {
        get { return m_warping; }
        set { m_warping = value; }
    }

    private void Start()
    {
        m_warping = false;
    }

    //  ��������
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  ���[�v���Ă������̓v���C���[�ȊO�͏������Ȃ�
        if (m_warp.GetSetWarping || !collision.gameObject.CompareTag("Player")) return;

        //  ���[�v�ɓ�����
        m_warping = true;
        //  �ړ�������
        collision.gameObject.transform.position = m_warp.transform.position;
    }
    //  �O�ꂽ
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (m_warp.GetSetWarping) m_warp.GetSetWarping = false;
    }
}
