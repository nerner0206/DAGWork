using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using DG.Tweening;
using TMPro;

public enum ClearSelect
{
    Back = 0,
    ReStart,
    Next,

    OverID
};

public class ClearUIManager : MonoBehaviour
{
    //  �����摜�f��
    [SerializeField, Header("�����摜�f��")]
    private List<Sprite> m_numbers;

    /// <summary>
    /// �N���AUI
    /// </summary>
    [SerializeField, Tooltip("�w�i�摜")]
    private Image m_backImage;
    [SerializeField, Tooltip("�^�C�g���摜�}�X�N")]
    private Image m_titleImageMask;
    [SerializeField, Tooltip("�^�C�g���摜")]
    private Image m_titleImage;
    [SerializeField, Tooltip("�^�C�g���摜�}�X�N")]
    private Image m_timeImageMask;
    [SerializeField, Tooltip("�^�C���摜")]
    private Image m_timeImage;

    [SerializeField, Tooltip("���Ԃ̉摜")]
    private List<Image> m_timeImages;

    [SerializeField, Tooltip("�I���摜")]
    private List<Image> m_selectImages;
    [SerializeField, Tooltip("�e�[�v")]
    private List<Image> m_tapeImages;

    [SerializeField, Tooltip("�A�C�R�����쉹")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("���艹")]
    private AudioClip m_decideAudio;
    [SerializeField, Tooltip("�W���O����")]
    private AudioClip m_clearAudio;
    [SerializeField, Tooltip("�N���b�J�[��")]
    private AudioClip m_crackerAudio;
    [SerializeField, Tooltip("���o��")]
    private AudioClip m_pusyuAudio;
    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;

    [SerializeField, Header("���̓f�b�h�]�[��")]
    private float deadZone = 0.1f;
    [SerializeField, Header("���̓N�[���^�C��")]
    private float coolTime = 0.5f;

    //  �R���g���[���[
    private PlayerControll m_controll;

    //  �A�j���[�V�����̏I��
    private bool m_animFin;

    //  ���͔ԍ�
    private int m_controllNum;
    //  ����
    private float m_timer;
    //  �p�x
    private float m_radian;

    public void ClearDisplay(float clearTime, PlayerControll inputActions, int tapeNum)
    {
        //  ���͂��󂯎��
        m_controll = inputActions;

        //  �������߂�
        int m = (int)clearTime / 60;
        //  �b�����߂�
        int s = (int)clearTime - m * 60;

        //  �����X�ɂP�ƂP�O�̈ʂɕ�����
        int m_ten = m / 10;
        int m_one = m % 10;

        //  �b���X�ɂP�ƂP�O�̈ʂɕ�����
        int s_ten = s / 10;
        int s_one = s % 10;

        //  �摜�̕ύX
        m_timeImages[0].sprite = m_numbers[m_ten];
        m_timeImages[1].sprite = m_numbers[m_one];
        m_timeImages[2].sprite = m_numbers[s_ten];
        m_timeImages[3].sprite = m_numbers[s_one];

        //  ������
        Init();

        //  �����x��߂�
        for (int i = 0; i < tapeNum; i++)
        {
            m_tapeImages[i].color = new Color(1f, 1f, 1f, 1f);
        }

        ////  �_�C�A���O�\��
        var sequence = DOTween.Sequence()
            //  �w�i�摜������
            .Append(m_backImage.rectTransform.DOLocalMoveY(0.0f, 0.5f).SetEase(Ease.OutElastic))
            //  �^�C�g���摜��������`��
            .Append(m_titleImageMask.rectTransform.DOSizeDelta(new Vector2(455.0f, 151.2f), 1.0f))
            //  �^�C���摜��������`��
            .Append(m_timeImageMask.rectTransform.DOSizeDelta(new Vector2(514.0f, 121.5f), 1.0f))
            //  �e�[�v�摜�̃T�C�Y��傫������
            .AppendCallback(() => m_tapeImages[0].rectTransform.sizeDelta = new Vector2(360.0f, 360.0f))
            .AppendCallback(() => m_tapeImages[1].rectTransform.sizeDelta = new Vector2(360.0f, 360.0f))
            .AppendCallback(() => m_tapeImages[2].rectTransform.sizeDelta = new Vector2(360.0f, 360.0f))
            //  �e�[�v�摜�̃T�C�Y��߂�
            .Append(m_tapeImages[0].rectTransform.DOSizeDelta(new Vector2(312.0f, 312.0f), 0.2f))
            .Join(m_tapeImages[1].rectTransform.DOSizeDelta(new Vector2(312.0f, 312.0f), 0.2f))
            .Join(m_tapeImages[2].rectTransform.DOSizeDelta(new Vector2(312.0f, 312.0f), 0.2f));

        //  �I���A�C�R���̕`��
        sequence
            .Append(m_selectImages[0].DOFade(1f, 0.1f))
            .Append(m_selectImages[1].DOFade(1f, 0.1f))
            .Append(m_selectImages[2].DOFade(1f, 0.1f))
            .AppendCallback(() => m_animFin = true);
    }

    private void Init()
    {
        m_controllNum = (int)ClearSelect.Next;
        m_timer = 0f;

        //  �w�i�摜�̈ʒu
        m_backImage.transform.localPosition = new Vector3(0.0f, 1000.0f, 0.0f);

        //  �^�C�g���}�X�N�̃T�C�Y��ݒ�
        m_titleImageMask.rectTransform.sizeDelta = new Vector2(0.0f, 126.0f);
        //  �^�C���}�X�N�̃T�C�Y��ݒ�
        m_timeImageMask.rectTransform.sizeDelta = new Vector2(0.0f, 121.5f);

        //  �e�[�v�̃T�C�Y��S��0�ɂ���
        for (int i = 0; i < m_tapeImages.Count; i++)
        {
            m_tapeImages[i].rectTransform.sizeDelta = Vector2.zero;
            m_tapeImages[i].color = new Color(1f, 1f, 1f, 0f);
        }
        //  �I�����ډ摜�̓�����
        for (int i = 0; i < m_selectImages.Count; i++)
        {
            m_selectImages[i].color = new Color(1f, 1f, 1f, 0f);
        }
        
        //  �A�j���[�V�����𖢏I����
        m_animFin = false;

        m_radian = 0.0f;

        //  �W���O����炷
        m_audioSource.PlayOneShot(m_clearAudio);
        m_audioSource.PlayOneShot(m_crackerAudio);
        m_audioSource.PlayOneShot(m_crackerAudio);
        m_audioSource.PlayOneShot(m_pusyuAudio);
    }

    public bool ClearUIUpdate()
    {
        if (!m_animFin) return false;

        m_radian += Mathf.PI / 180.0f * 1.5f;
        m_selectImages[m_controllNum].transform.localScale = Vector3.one + (new Vector3(0.1f, 0.1f, 0.1f) * Mathf.Sin(m_radian));

        //  �l�����
        float move = m_controll.PlaySceneUI.Move.ReadValue<float>();
        //  ���͂�����
        if (Mathf.Abs(move) > deadZone)
        {
            if(m_timer <= 0f)
            {
                m_audioSource.PlayOneShot(m_moveAudio);
                if (move > 0f) m_controllNum++;
                else m_controllNum--;

                if (m_controllNum > (int)ClearSelect.Next) m_controllNum = (int)ClearSelect.Next;
                else if (m_controllNum < (int)ClearSelect.Back) m_controllNum = (int)ClearSelect.Back;

                m_radian = 0.0f;

                m_timer = coolTime;
            }
            else
            {
                m_timer -= Time.deltaTime;
            }
        }
        else
        {
            m_timer = 0f;
        }

        //  ����
        if(m_controll.PlaySceneUI.Decide.WasPressedThisFrame())
        {
            m_audioSource.PlayOneShot(m_decideAudio);
            return true;
        }
        return false;
    }

    public int ClearSelectNum()
    {
        return m_controllNum;
    }
}
