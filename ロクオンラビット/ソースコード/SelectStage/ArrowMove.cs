using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class ArrowMove : MonoBehaviour
{
    [SerializeField, Tooltip("�ړ����x")]
    private float m_moveSpeed = 1.0f;
    [SerializeField, Tooltip("�ړ���")]
    private float m_moveRange;

    //  �p�x
    private float m_radian;
    //  �ŏ��̈ʒu
    private Vector3 m_startPos;


    private void Start()
    {
        m_radian = 0.0f;

        m_startPos = gameObject.transform.position;
    }

    private void Update()
    {
        //  �p�x����
        m_radian += Mathf.PI / 180.0f * m_moveSpeed * Time.deltaTime;
        if(m_radian >= 2 * Mathf.PI) m_radian = 0.0f;

        //  �ʒu
        Vector3 pos = gameObject.transform.position;
        //  �㉺�ړ�
        pos.y = m_startPos.y + Mathf.Sin(m_radian) * m_moveRange;
        //  �ʒu�X�V
        gameObject.transform.position = pos;
    }
}
