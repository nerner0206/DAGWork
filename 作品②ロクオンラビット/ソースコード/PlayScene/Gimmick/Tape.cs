using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tape : MonoBehaviour
{
    //  �擾������
    private bool m_isTape = false;
    //  ���[�J�����W
    private Vector3 m_position;
    //  �p�x
    private float m_angle;

    //  �󂯓n��
    public bool GetSetTape
    {
        get { return m_isTape; }
        set { m_isTape = value; }
    }

    private void Start()
    {
        m_position = this.transform.localPosition;
        m_angle = 0f;
    }

    private void Update()
    {
        m_angle += Time.deltaTime;
        m_position = this.transform.localPosition;

        m_angle %= 360f;

        float posY = Mathf.Cos(m_angle) * 0.001f;

        Vector3 delta = new Vector3(0f, posY, 0f);
        
        this.transform.localPosition = m_position + delta;
    }

    //  ������
    public void Init()
    {
        m_isTape = false;
    }

    //  �����蔻��
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  �擾�ς݂ɂ���
        m_isTape = true;
    }
}
