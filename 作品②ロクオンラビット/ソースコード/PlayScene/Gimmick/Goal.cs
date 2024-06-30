using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Goal : MonoBehaviour
{
    //  �S�[������
    private bool m_isGoal = false;

    //  �擾�E�n��
    public bool GetSetIsGoal
    {
        get { return m_isGoal; }
        set { m_isGoal = value; }
    }

    //  �����蔻��
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  �v���C���[�ȊO�Ȃ珈�����Ȃ�
        if (!collision.gameObject.CompareTag("Player")) return;

        //  �S�[��
        m_isGoal = true;
    }
}
