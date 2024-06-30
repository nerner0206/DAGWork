using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class WoodBoxCreator : PlayElecObj
{
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;

    [SerializeField, Tooltip("�������锠�̃v���n�u")]
    private GameObject m_boxPrefab;

    [Header("�������")]

    [SerializeField, Tooltip("�������锠�̏��")]
    private int m_maxNum = 1;
    [SerializeField, Tooltip("�����ɑ��݂ł��锠�̐�")]
    private int m_sameNum = 1;
    [SerializeField, Tooltip("�������Ԃ̊Ԋu")]
    private float m_createTime = 5.0f;
    [SerializeField, Tooltip("�����ʒu")]
    private Transform m_createPos;
    [SerializeField, Tooltip("�v���C���[�̈ʒu")]
    private Transform m_player;

    //  �����������̐�
    private int m_createNum;
    //  ���݂��Ă��锠�̐�
    private int m_nowNum;
    //  �^�C�}�[
    private float m_timer;
    //  ���������I�u�W�F�N�g���i�[����z��
    private WoodBox[] m_boxes;
    //  ����AudioSourcs
    private AudioSource[] m_boxesAudio;

    //  ��ꂽ�I�u�W�F�N�g���i�[����z��
    private GameObject breakboxes;

    //  ������
    public override void Init()
    {
        //  ������
        m_createNum = 0;
        m_nowNum = 0;
        //  ����
        m_timer = 0f;
        //  ������
        m_boxes = new WoodBox[m_sameNum];
        m_boxesAudio = new AudioSource[m_sameNum];

        breakboxes = null;
    }

    //  �X�V
    private void Update()
    {
        for (int i = 0; i < m_nowNum; i++)
        {
            //  �������������珈�����Ȃ�
            if (m_boxes[i] == null) continue;

            //  �������Ă��Ȃ�
            if (!m_boxes[i].GetSetIsBreak) continue;

            if (breakboxes != null) Destroy(breakboxes);

            breakboxes = m_boxes[i].gameObject;

            //  �j�󂳂�Ă���
            for (int j = i;j < m_nowNum - 1;j++)
            {
                //  �㏑��
                m_boxes[j] = m_boxes[j + 1];
                m_boxesAudio[j] = m_boxesAudio[j + 1];
            }
            //  �Ō�̗v�f��null�ɂ���
            m_boxes[m_nowNum - 1] = null;
            m_boxesAudio[m_nowNum - 1] = null;
            //  ���炷
            m_nowNum--;
        }

        //  ���ʒ���
        for (int i = 0; i < m_nowNum; i++)
        {
            //  �������������珈�����Ȃ�
            if (m_boxes[i] == null) continue;

            //  �M�~�b�N���ƃv���C���[�̋����𑪂�
            float distance = Vector3.Distance(m_player.position, m_boxes[i].gameObject.transform.position);
            //  �ő勗���Ƃ̊���
            float vol = 1 - (distance / 10);
            //  ���ʂ��}�C�i�X�ɂȂ�����O�ɖ߂�
            if (vol < 0) vol = 0f;
            //  ���ʂ�ݒ�
            m_boxesAudio[i].volume = vol;
        }

        //  �ʓd���Ă��Ȃ������珈�����Ȃ�
        if (!m_hitElec) return;

        //  ���������ő吔�𒴂����珈�����Ȃ� || ��������-1�Ȃ疳���ɐ�������
        if (m_maxNum != -1)
        {
            if (m_createNum >= m_maxNum) return;
        }

        //  ���Ԃ𑝂₷
        m_timer += Time.deltaTime;

        //  ���݂��Ă��锠�̐�������𒴂��Ă���
        if (m_nowNum >= m_sameNum) return;
        //  �������Ԃ�菬����
        if (m_timer < m_createTime) return;

        //  �������鏈��
        Create();
    }

    //  �������鏈��
    private void Create()
    {
        m_animator.SetTrigger("Create");

        //  ��������
        GameObject box = Instantiate(m_boxPrefab,
            m_createPos.position,
            Quaternion.identity);

        //  ���̃T�C�Y�𐶐���ɍ��킹��
        box.transform.localScale *= gameObject.transform.localScale.x;
        //  �����ʒu�̒���

        //  �i�[����
        m_boxes[m_nowNum] = box.GetComponent<WoodBox>();
        m_boxesAudio[m_nowNum] = box.GetComponent<AudioSource>();

        //  �^�C�}�[��������
        m_timer = 0f;
        //  ������������������
        m_createNum++;
        m_nowNum++;
    }

    //  ���Z�b�g
    public override void GimmickReset()
    {
        //  ������
        m_createNum = 0;
        m_nowNum = 0;
        //  ����
        m_timer = 0f;
        //  ������
        for (int i = 0; i < m_sameNum; i++) 
        {
            if (m_boxes[i] != null) Destroy(m_boxes[i].gameObject);
            m_boxesAudio[i] = null;
        }

        //  ������
        m_boxes = new WoodBox[m_sameNum];

        breakboxes = null;
    }

    //  �d�C�̐ڐG
    public override void HitElec()
    {
        base.HitElec();
    }
}
