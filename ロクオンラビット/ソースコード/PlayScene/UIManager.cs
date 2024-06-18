using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class UIManager : MonoBehaviour
{
    [SerializeField, Tooltip("UI�̐e")]
    private GameObject m_parent;

    [SerializeField, Header("���̃A�C�R��")]
    private List<GameObject> m_soundIconsPrefab;
    [SerializeField, Header("���̃A�C�R���t���[��")]
    private GameObject[] m_soundFrames;

    [SerializeField, Tooltip("���W�v�f�̐ݒ�")]
    private GameObject[] m_collectItems;
    [SerializeField, Tooltip("�Đ��󋵂̃A�C�R��")]
    private GameObject[] m_playIcons = new GameObject[2];

    //  ���Ă�ő�̐�
    private int m_maxNum;

    //  �N���ACanvas
    [SerializeField] private ClearUIManager m_clear;

    //  �R���g���[���[
    private PlayerControll m_controll;

    //  ���X�^�[�gObj
    [SerializeField] private GameObject m_reStartObj;
    //  �Q�[�W
    [SerializeField] private Image m_reStartGage;
    //  ���X�^�[�g����
    [SerializeField] private float m_reStartTime;
    //  ���X�^�[�g�^�C�}�[
    private float m_reStartTimer;

    [SerializeField, Tooltip("�ȈՃt�F�C�h�C���A�E�g�p")]
    private ScreenFade m_fade;

    //  UI�̔�\��
    public void Non()
    {
        m_parent.SetActive(false);
    }
    //  UI�̕\��
    public void On()
    {
        m_parent.SetActive(true);
    }

    //  ������
    public void UIManagerInit(PlayerHaveSound p, PlayerControll inputActions)
    {
        //  �R���g���[���[
        m_controll = inputActions;

        //  �������Ă�ő�̐����擾
        m_maxNum = p.GetMaxHaveSound();

        //  ���Ă鐔�܂�UI�����炷
        for (int i = m_maxNum; i < m_soundFrames.Length; i++)
        {
            m_soundFrames[i].SetActive(false);
        }
        //  ������
        for (int i = 0; i < m_collectItems.Length; i++)
        {
            m_collectItems[i].SetActive(false);
        }

        //  ���X�^�[�g�Q�[�W
        m_reStartTimer = 0f;
    }
    //  UI�̍X�V
    public bool UIUpdate()
    {
        //  ��������
        if(m_controll.PlaySceneUI.ReStart.WasPressedThisFrame())
        {
            //  RestartUI�\��
            m_reStartObj.SetActive(true);
            //  �^�C�}�[�̏�����
            m_reStartTimer = 0f;
        }

        //  ��������
        if(m_controll.PlaySceneUI.ReStart.WasReleasedThisFrame())
        {
            //  RestartUI��\��
            m_reStartObj.SetActive(false);
        }
        //  ��������
        else if(m_controll.PlaySceneUI.ReStart.ReadValue<float>() > 0.5f)
        {
            //  ���Ԃ𑝂₷
            m_reStartTimer += Time.deltaTime;

            m_reStartGage.fillAmount = m_reStartTimer / m_reStartTime;

            if (m_reStartTimer >= m_reStartTime)
            {
                //  UI�̔�\��
                m_reStartObj.SetActive(false);
                return true;
            }
        }

        return false;
    }

    //  �N���A�X�V�̐^�U�l�̎擾
    public bool ClearUIUpdate()
    {
        return m_clear.ClearUIUpdate();
    }
    //  �I��ԍ��̎擾
    public int ClearUISelectNumber()
    {
        return m_clear.ClearSelectNum();
    }

    //  �擾�������̃A�C�R���̐ݒ�
    public void SetSoundIconUI(SoundKind[] soundKinds, bool[] playbacks)
    {
        for (int i = 0; i < soundKinds.Length; i++)
        {
            int n = m_soundFrames[i].transform.childCount;

            //  ���̃A�C�R�����폜����
            for (int j = 0; j < n; j++)
            {
                Destroy(m_soundFrames[i].transform.GetChild(j).gameObject);
            }

            //  ����������Ώ������Ȃ�
            if (soundKinds[i] == SoundKind.Over) continue;

            int num = (int)soundKinds[i];
            if (num > (int)SoundKind.Over) num = (int)SoundKind.Over;

            //  ���ɍ������I�u�W�F�N�g�𐶐�����
            GameObject icon = Instantiate(m_soundIconsPrefab[num], m_soundFrames[i].transform);
            icon.transform.localPosition = Vector3.zero;

            //  �Đ��A�C�R��
            GameObject playIcon = null;
            //  ���ʍĐ�
            if (playbacks[i]) playIcon = Instantiate(m_playIcons[0], icon.transform);
            //  �t�Đ�
            else playIcon = Instantiate(m_playIcons[1], icon.transform);

            RectTransform rect = playIcon.GetComponent<RectTransform>();
            //  �傫���̕ύX
            if (i != 0)
            {
                icon.GetComponent<RectTransform>().sizeDelta = new Vector2(90, 90);
                rect.localPosition = new Vector3(20, -20, 0);
                rect.sizeDelta = new Vector2(66, 66);
            }
            else
            {
                icon.GetComponent<RectTransform>().sizeDelta = new Vector2(140, 140);
                rect.localPosition = new Vector3(30, -30, 0);
            }
            
        }
    }

    //  ���W�v�f�̐ݒ�
    public void SetTapeUI(bool[] flags)
    {
        for (int i = 0; i < flags.Length; i++)
        {
            if (flags[i]) m_collectItems[i].SetActive(true);
        }
    }

    //  �N���A��ʂ̕\��
    public void Clear(float time, int tapeNum)
    {
        //  �N���AUI�̕\��
        m_clear.gameObject.SetActive(true);
        //  �\��
        m_clear.ClearDisplay(time, m_controll, tapeNum);
    }

    //  �N���A���ڂ̔�\��
    public void ClearReset()
    {
        m_clear.gameObject.SetActive(false);
    }

    //  �t�F�C�h�C���J�n
    public void FadeInStart()
    {
        m_fade.PlayFadeIn();
    }
    //  �t�F�C�h�A�E�g�J�n
    public void FadeOutStart()
    {
        m_fade.PlayFadeOut();
    }

    //  ���X�^�[�g
    public bool ReStart()
    {
        return m_fade.EndFadeOut();
    }
}
