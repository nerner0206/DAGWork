using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveNoise : MonoBehaviour
{
    [SerializeField, Tooltip("�J�n�ʒu")]
    private Vector3 m_startPos;
    [SerializeField, Tooltip("�I���ʒu")]
    private Vector3 m_endPos;

    [SerializeField, Tooltip("�������x")]
    private float m_speed;

    //  �����Ă������
    private bool m_flag;
    //  ����
    private float m_ratio;   
    
    void Start()
    {
        //  �X�^�[�g�ʒu�Ɉړ�
        this.transform.localPosition = m_startPos;
    }

    void Update()
    {
        //  �t���O�ɉ�����_t�ɉ��Z
        if (m_flag)
        {
            m_ratio += Time.deltaTime * m_speed;
        }
        else
        {
            m_ratio -= Time.deltaTime * m_speed;
        }

        //  ���l�ŕ����]��
        if (m_ratio > 1f)  m_flag = false;
        else if (m_ratio < 0f) m_flag = true;

        //  ���[�v
        float x = Mathf.Lerp(m_startPos.x, m_endPos.x, m_ratio);

        this.transform.localPosition = new Vector3(
            x,
            this.transform.localPosition.y,
            this.transform.localPosition.z
        );
    }
}
