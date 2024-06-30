using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConfigManager : MonoBehaviour
{
    //  �ݒ�{�^��
    [SerializeField] private GameObject configButton;
    //  ����{�^��
    [SerializeField] private GameObject closeButton;
    //  �Ό둀��p�p�l��
    [SerializeField] private GameObject backPanel;

    //  �ݒ�{�^������������
    public void PushConfigButton()
    {
        //  �ݒ�{�^�����\��
        configButton.SetActive(false);
        //  �p�l����\��
        backPanel.SetActive(true);

        //  �����~�߂�
        Time.timeScale = 0.0f;
    }
    //  ����{�^������������
    public void PushCloseButton()
    {
        //  �p�l�����\��
        backPanel.SetActive(false);
        //  �ݒ�{�^����\��
        configButton.SetActive(true);

        //  ���𓮂���
        Time.timeScale = 1.0f;
    }

    //  �Q�[�����I��
    public void PushEndButton()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#else
    Application.Quit();
#endif
    }
}
