using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NaughtyAttributes;

public class SelectUI : MonoBehaviour
{
    [SerializeField, Tooltip("��")]
    private Image[] m_starImages;
    [SerializeField, Tooltip("�X�e�[�W�摜")]
    private Image[] m_stageImages;
    [SerializeField, Tooltip("�X�e�[�W�^�C�g��")]
    private Text m_titleText;
    [SerializeField, Tooltip("�X�e�[�W����")]
    private Text m_stageText;

    [SerializeField, Header("�e�X�e�[�W�̃^�C�g��")]
    private string[] m_titles;
    [SerializeField, ResizableTextArea, Header("�e�X�e�[�W�̐�����")]
    private string[] m_stageInfos;

    public void SetUI(int num)
    {
        //  ���̐�
        SetStar(num);
        SetStage(num);
        SetText(num);
    }

    private void SetStar(int num)
    {
        //  �S��\��
        for (int i = 0; i < m_starImages.Length; i++)
        {
            m_starImages[i].enabled = false;
        }

        //  �����\��
        for (int i = 0; i < num + 1; i++)
        {
            m_starImages[i].enabled = true;
        }
    }
    private void SetStage(int num)
    {
        //  �S��\��
        for (int i = 0; i < m_stageImages.Length; i++)
        {
            m_stageImages[i].enabled = false;
        }

        //  �\��
        m_stageImages[num].enabled = true;
    }
    private void SetText(int num)
    {
        //  �S��\��
        m_titleText.text = m_titles[num];
        m_stageText.text = m_stageInfos[num];
    }
}
