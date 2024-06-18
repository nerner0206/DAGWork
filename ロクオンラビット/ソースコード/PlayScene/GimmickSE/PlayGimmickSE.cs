using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class PlayGimmickSE : GimmickSE
{
    //  �~�̓����蔻��
    private CircleCollider2D m_co2D = null;

    public void Init()
    {
        //  ���̎�ނ�����
        m_soundKind = SoundKind.Over;
        //  �~�̓����蔻��
        m_co2D = gameObject.GetComponent<CircleCollider2D>();
        //  �����蔻�����
        m_co2D.enabled = false;
    }
    public void OnGimmickSE(SoundKind kind)
    {
        //  ���̎��
        m_soundKind = kind;

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
}
