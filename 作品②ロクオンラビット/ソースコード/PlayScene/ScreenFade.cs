using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NaughtyAttributes;

public class ScreenFade : MonoBehaviour
{
    [SerializeField, Tooltip("�E�����ɓ����p�l��")]
    private RectTransform[] m_rightPanels;

    [SerializeField, Tooltip("�������ɓ����p�l��")]
    private RectTransform[] m_leftPanels;

    [SerializeField, Tooltip("�t�F�[�h�̓����p��AnimationCurve")]
    private AnimationCurve m_fadeCurve;

    [SerializeField, Tooltip("���쎞��")]
    private float m_playTime;

    [ShowNonSerializedField] private bool m_isFadeOut;            //  �t�F�[�h�A�E�g���쒆
    [ShowNonSerializedField] private bool m_isFadeIn;             //  �t�F�[�h�C�����쒆

    private float m_screenWidth;         //  ��ʂ̉��̑傫��
    private float m_timer;               //  ���쎞�Ԍv��
    private bool m_beforeOut;            //  �O�t���[���̃t�F�[�h�A�E�g����
    private bool m_beforeIn;             //  �O�t���[���̃t�F�[�h�C������

    private void Start()
    {
        //  ��ʃT�C�Y�擾
        m_screenWidth = Screen.width;

        //  ������
        m_timer = 0f;
        m_isFadeOut = false;
        m_isFadeIn  = false;
        m_beforeOut = false;
        m_beforeIn  = false;
    }

    private void Update()
    {
        //  �O�t���[���m�F�p�̃t���O���X�V
        m_beforeOut = m_isFadeOut;
        m_beforeIn = m_isFadeIn;

        //  ���쎞�ԂɂȂ����瓮�����~�߂�
        if (m_timer >= m_playTime)
        {
            m_isFadeOut = false;
            m_isFadeIn = false;
            return;
        }

        //  �^�C�}�[�̍X�V
        m_timer += Time.deltaTime;

        //  �o�ߎ��Ԃ̊������v�Z
        float rate = m_timer / m_playTime;

        //  AnimationCurve��K�p
        float curve = m_fadeCurve.Evaluate(rate);

        //  �t�F�[�h�A�E�g�����쒆�̏ꍇ
        if (m_isFadeOut)
        {
            //  �ړ���̌v�Z
            float rightMove = Mathf.Lerp(-m_screenWidth, 0f, curve);
            float leftMove  = Mathf.Lerp(m_screenWidth, 0f, curve);

            //  �ړ�����
            foreach (var p in m_rightPanels)
            {
                p.localPosition = new Vector3(rightMove, p.localPosition.y, 0f);
            }

            foreach (var p in m_leftPanels)
            {
                p.localPosition = new Vector3(leftMove, p.localPosition.y, 0f);
            }
        }
        //  �t�F�[�h�C�������쒆�̏ꍇ
        else if (m_isFadeIn)
        {
            //  �ړ���̌v�Z
            float rightMove = Mathf.Lerp(0f, m_screenWidth, curve);
            float leftMove = Mathf.Lerp(0f, -m_screenWidth, curve);

            //  �ړ�����
            foreach (var p in m_rightPanels)
            {
                p.localPosition = new Vector3(rightMove, p.localPosition.y, 0f);
            }

            foreach (var p in m_leftPanels)
            {
                p.localPosition = new Vector3(leftMove, p.localPosition.y, 0f);
            }
        }
    }

    /// <summary>
    /// �t�F�[�h�A�E�g(��ʂ��Â��Ȃ�)�̍Đ��J�n
    /// </summary>
    [Button("�t�F�[�h�A�E�g�e�X�g")]
    public void PlayFadeOut()
    {
        //  �t�F�[�h�C�������s���Ȃ�t�F�[�h�A�E�g�ł��Ȃ��悤�ɂ���
        if (m_isFadeIn) return;

        //  �t���O�̕ύX
        m_isFadeOut = true;
        m_timer = 0f;

        //  �����ʒu�֐ݒu
        foreach (var p in m_rightPanels)
        {
            p.localPosition = new Vector3(-m_screenWidth, p.localPosition.y, 0f);
        }

        foreach (var p in m_leftPanels)
        {
            p.localPosition = new Vector3(m_screenWidth, p.localPosition.y, 0f);
        }
    }

    /// <summary>
    /// �t�F�[�h�A�E�g�̍Đ����I������u��true��Ԃ�
    /// </summary>
    public bool EndFadeOut()
    {
        return !m_isFadeOut && m_beforeOut;
    }

    /// <summary>
    /// �t�F�[�h�C��(��ʂ𖾂邭����)�̍Đ��J�n
    /// </summary>
    [Button("�t�F�[�h�C���e�X�g")]
    public void PlayFadeIn()
    {
        //  �t�F�[�h�A�E�g�����s���Ȃ�t�F�[�h�C���ł��Ȃ��悤�ɂ���
        if (m_isFadeOut) return;

        //  �t���O�̕ύX
        m_isFadeIn = true;
        m_timer = 0f;

        //  �����ʒu�֐ݒu
        foreach (var p in m_rightPanels)
        {
            p.localPosition = new Vector3(0f, p.localPosition.y, 0f);
        }

        foreach (var p in m_leftPanels)
        {
            p.localPosition = new Vector3(0f, p.localPosition.y, 0f);
        }
    }

    /// <summary>
    /// �t�F�[�h�C���̍Đ����I������u��ture��Ԃ�
    /// </summary>
    /// <returns></returns>
    public bool EndFadeIn()
    {
        return !m_isFadeIn && m_beforeIn;
    }
}
