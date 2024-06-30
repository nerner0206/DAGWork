using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BeltConveyor : MonoBehaviour
{
    [SerializeField, Tooltip("�I�u�W�F�N�g��������")]
    private float m_pushForce = 30f;

    [SerializeField, Tooltip("�I�u�W�F�N�g�̖ڕW���x")]
    private float m_TargetDriveSpeed = 3f;

    //  �x���g�R���x�A�̉ғ���
    private bool m_isOn;
    //  �ړ����x
    private float m_moveSpeed;
    //  �͂̕���
    private Vector2 m_pushDir;

    //  �ڐG�����I�u�W�F�N�g
    private List<Rigidbody2D> m_rigidbody2Ds;

    //  �x���g�R���x�A�̉ғ��󋵎擾�E�ݒ�
    public bool GetSetIsOn
    {
        get { return m_isOn; }
        set { m_isOn = value; }
    }

    public void Init(bool flag)
    {
        //  �ғ���
        m_isOn = flag;
        //  ���X�g��������
        m_rigidbody2Ds = new List<Rigidbody2D>();

        m_moveSpeed = 0.0f;
    }

    private void FixedUpdate()
    {
        //  �ғ����Ă��Ȃ��E�ڐG�I�u�W�F�N�g���Ȃ��Ȃ珈�����Ȃ�
        if (!m_isOn || m_rigidbody2Ds == null) return;

        //���ł����I�u�W�F�N�g�͏�������
        m_rigidbody2Ds.RemoveAll(r => r == null);
        if(m_rigidbody2Ds == null) return;

        foreach (var r in m_rigidbody2Ds)
        {
            //���̂̈ړ����x�̃x���g�R���x�A�����̐������������o��
            var objectSpeed = Vector2.Dot(r.velocity, m_pushDir);

            //�ڕW�l�ȉ��Ȃ��������
            if (objectSpeed >= Mathf.Abs(m_TargetDriveSpeed)) continue;
            //  �͂�^����
            r.AddForce(m_pushDir * m_pushForce * m_moveSpeed, ForceMode2D.Force);
        }
    }

    //  �I�u�W�F�N�g���ڐG
    private void OnCollisionEnter2D(Collision2D collision)
    {
        //  �R���|�[�l���g���������Ă��Ȃ�
        if (collision.gameObject.TryGetComponent(out Rigidbody2D rb2D))
        {
            //  �ǉ�
            m_rigidbody2Ds.Add(rb2D);

            rb2D.constraints = RigidbodyConstraints2D.FreezeRotation;
        }
    }
    //  �I�u�W�F�N�g�������
    private void OnCollisionExit2D(Collision2D collision)
    {
        //  �R���|�[�l���g���������Ă��Ȃ�
        if (collision.gameObject.TryGetComponent(out Rigidbody2D rb2D))
        {
            //  �폜
            m_rigidbody2Ds.Remove(rb2D);
        }
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        //  �R���|�[�l���g���������Ă��Ȃ�
        if (collision.gameObject.TryGetComponent(out Rigidbody2D rb2D))
        {
            rb2D.constraints = RigidbodyConstraints2D.FreezeRotation;
        }
    }

    //  �͂̕�����ݒ肷��
    public void SetPushDir(float angle, float animSpeed)
    {
        //  �����i�O�x�j
        Vector2 dir = Vector2.right;

        //  �p�x��ݒ�
        m_pushDir.x = dir.x * Mathf.Cos(angle);
        m_pushDir.y = dir.x * Mathf.Sin(angle);

        //  �A�j���X�s�[�h�𔽉f������
        m_pushDir *= animSpeed;
        m_moveSpeed = Mathf.Abs(animSpeed);

        //  �P�ʃx�N�g��
        m_pushDir.Normalize();
    }
}
