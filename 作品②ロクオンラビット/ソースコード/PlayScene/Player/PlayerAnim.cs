using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnim : MonoBehaviour
{
    //  �X�^�[�g���}�̎擾�E�ݒ�
    public bool GetSetIsStart
    {
        get { return m_isStart; }
        set { m_isStart = value; }
    }

    //  �Q�[���I�[�o�[����̎擾�E�ݒ�
    public bool GetSetIsGameOver
    {
        get { return m_isGameOver; }
        set { m_isGameOver = value; }
    }

    //  �U���̎擾�E�ݒ�
    public bool GetSetAttack
    {
        get { return m_attack; }
        set { m_attack = value; }
    }

    //  �X�^�[�g���}
    private bool m_isStart = false;
    //  �Q�[���I�[�o�[����
    private bool m_isGameOver = false;
    //  �U��
    private bool m_attack = false;

    //  ���S�A�j���[�V�����I��
    void FinishDeadAnimation()
    {
        //  �Q�[���I�[�o�[
        m_isGameOver = true;
    }
    //  �J�n�A�j���[�V�����I��
    void FinishStartAnimation()
    {
        //  ������
        m_isStart = true;
    }
    //  �U���A�j���[�V�����̃^�C�~���O
    void Attack()
    {
        m_attack = true;
    }
}
