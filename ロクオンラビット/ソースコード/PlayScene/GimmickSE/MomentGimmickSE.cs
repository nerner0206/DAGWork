using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class MomentGimmickSE : GimmickSE
{
    [SerializeField, Tooltip("�~�̓����蔻��")]
    private CircleCollider2D m_co2D;
    //  ����
    private float m_timer;

    public void Init()
    {
        //  ���̎�ނ�����
        m_soundKind = SoundKind.Over;
        //  �����蔻�����
        m_co2D.enabled = false;

        //  ���Ԃ�0��
        m_timer = 0.0f;
    }
    public void OnGimmickSE(SoundKind kind, float time)
    {
        //  ���̎��
        m_soundKind = kind;
        //  ���擾�\����
        m_timer = time;

        //  �����蔻�������
        m_co2D.enabled = true;
    }
    public void OffGimmickSE()
    {
        //  ���̎��
        m_soundKind = SoundKind.Over;

        //  �����蔻�������
        m_co2D.enabled = false;
    }

    private void Update()
    {
        //  ����������Ώ������Ȃ�
        if (m_soundKind == SoundKind.Over) return;

        if (m_timer > 0.0f)
        {
            //  ���Ԃ����炷
            m_timer -= Time.deltaTime;
            //  �Ԃ�
            return;
        }

        //  �����蔻����폜
        OffGimmickSE();
    }
}
