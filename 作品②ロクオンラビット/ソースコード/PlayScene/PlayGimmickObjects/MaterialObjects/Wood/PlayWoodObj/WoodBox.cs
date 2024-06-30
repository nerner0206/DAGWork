using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
[RequireComponent(typeof(Rigidbody2D))]
public class WoodBox : PlayWoodObj
{
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;
    [SerializeField, Tooltip("����")]
    private Rigidbody2D m_rb;
    [SerializeField, Tooltip("�����E����͈�")]
    private MomentGimmickSE m_gimmickSE;
    [SerializeField, Tooltip("�j��ς�")]
    private bool m_isBreak = false;
    [SerializeField, Tooltip("���C���΂��ʒu")]
    private Transform m_rayPos;
    
    [SerializeField, Tooltip("���̑f��")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("�j��")]
    private float m_breakPower;

    [SerializeField, Tooltip("�ؔ��j��G�t�F�N�g")]
    private ParticleSystem m_breakEffect;

    //  �j���Ԃ̎擾�E�ݒ�
    public bool GetSetIsBreak
    {
        get { return m_isBreak; }
        set { m_isBreak = value; }
    }

    public override void Init()
    {
        //  �������ʉ��ɕς���
        m_audioSource.clip = m_audioClips[0];

        //  ������
        m_gimmickSE.Init();
        //  ����
        m_gimmickSE.OffGimmickSE();

        if (!m_isBreak) return;
        //  �ŏ�������Ă���
        //  �ʏ�Đ�
        Breaking();
    }

    //  �����q�b�g
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �f�t�H���g���g�p
        base.SoundHit(kind, pitch, audioClip);
    }
    //  �j�󉹂ŉ󂷏���
    public override void HitBreak(float pitch) 
    {
        //  �t�Đ������肷��&&���ɉ��Ă���
        if(pitch < 0 && m_isBreak)
        {
            //  ����
            m_isBreak = false;
            //  �C���A�j���[�V�������Đ�
            m_animator.SetBool("Break", m_isBreak);

            //  ���C���[��؂�ւ���
            int layer = LayerMask.NameToLayer("Box");
            gameObject.layer = layer;

            //  �������ʉ��ɕς���
            m_audioSource.clip = m_audioClips[0];
            //  �����E���Ȃ�����
            m_gimmickSE.OffGimmickSE();

            //  �����I��
            return;
        }
        else if(pitch > 0 && !m_isBreak)
        {
            //  �ʏ�Đ�
            Breaking();
        }
        
    }

    //  �j��
    private void Breaking()
    {
        //  ��
        m_isBreak = true;
        //  �j��A�j���[�V�������Đ�
        m_animator.SetBool("Break", m_isBreak);

        //  ���C���[��؂�ւ���
        int layer = LayerMask.NameToLayer("Breaking"); ;
        gameObject.layer = layer;

        //  ����j�󉹂ɕς���
        m_audioSource.clip = m_audioClips[1];
        //  �炷
        m_audioSource.Play();
        m_breakEffect.Play();
        //  �j�󉹂̔���
        m_gimmickSE.OnGimmickSE(m_soundKind, 0.2f);

        //  ���̏ꍇ
        m_rb.constraints = RigidbodyConstraints2D.FreezePositionX
            | RigidbodyConstraints2D.FreezeRotation;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        //  �Փˎ��̗͂��擾
        float hitPower = collision.contacts[0].normalImpulse;
        //  �Փ˂̗͂���������Ώ������Ȃ�
        if (hitPower < m_breakPower || m_isBreak) return;

        //  �j��
        Breaking();
    }
    private void OnCollisionExit2D(Collision2D collision)
    {
        //  ���ꂽ�I�u�W�F�N�g���x���g�R���x�A�������Ă���
        if(collision.gameObject.TryGetComponent(out BeltConveyor belt))
        {
            //  ���C�����ɔ�΂�
            int layer = LayerMask.GetMask("Belt");
            //  Ray���΂�
            RaycastHit2D hitObj = Physics2D.CircleCast(m_rayPos.position, 0.5f, Vector2.zero, 0.0f, layer);
            //  �x���g�R���x�A������
            if (hitObj.collider != null)
            {
                //  �����Ă���Ȃ珈�����Ȃ�
                if (hitObj.collider.GetComponent<PlayBeltObj>().GetSetIsMove) return;
                //  ���̏ꍇ
                m_rb.constraints = RigidbodyConstraints2D.FreezePositionX
                    | RigidbodyConstraints2D.FreezeRotation;
            }
            else
            {
                //  ���̏ꍇ
                m_rb.constraints = RigidbodyConstraints2D.FreezePositionX
                    | RigidbodyConstraints2D.FreezeRotation;
            }
        }
    }
}
