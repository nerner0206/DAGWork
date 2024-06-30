using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LogoSceneManager : SceneManagement
{
    //  �^�C�g���V�[���̏��
    private enum LogoSceneState
    {
        FadeIn,
        Main,
        FadeOut
    };

    [SerializeField, Tooltip("�\������")]
    private float displayTime = 1.0f;

    //  �R���g���[���[
    private PlayerControll m_controll;
    //  ���̃V�[��
    const AllScene m_thisScene = AllScene.LogoScene;
    //  �ݒ�
    private OptionUI m_option;
    //  �V�[���̏��
    private LogoSceneState m_sceneState;
    //  �^�C�}�[
    private float m_timer;

    private void Start()
    {
        //  ���͂̐���
        m_controll = new PlayerControll();
        m_controll.Enable();

        //  �I�v�V�����̐����Ə�����
        //  �I�v�V�����̐����Ə�����
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        m_option.Initialized(m_thisScene, m_controll);

        m_timer = displayTime;

        //  �t�F�C�h�C����Ԃɂ���
        m_sceneState = LogoSceneState.FadeIn;
        //  �t�F�C�h�C�����J�n����
        m_option.StartFadeIn(m_fadeTime);
    }

    private void Update()
    {
        //  �I�v�V�������J���Ă��鎞�͏������Ȃ�
        if (OptionUI.m_isOption) return;

        switch(m_sceneState)
        {
            case LogoSceneState.FadeIn:
                //  �t�F�C�h�C���̏I�����擾
                bool flag = m_option.GetFadeFinish();
                //  �I�����Ă��Ȃ�
                if(!flag) break;

                //  �I�������玟�̏�Ԃ�
                m_sceneState = LogoSceneState.Main;
                break;
            case LogoSceneState.Main:
                //  ����
                MainUpdate();
                
                break;
            case LogoSceneState.FadeOut:
                //  �t�F�C�h�A�E�g�̏I�����󂯎��
                flag = m_option.GetFadeFinish();

                if (!flag) break;
                
                //  �I�v�V�����̉�ʑJ�ڏ���
                m_option.Finish();
                //  �Z���N�g�V�[���ֈړ�����
                SceneManager.LoadScene(m_nextSceneNames[0]);
                break;
        }
    }

    //  �X�V����
    private void MainUpdate()
    {
        if(m_timer > 0.0f)
        {
            m_timer -= Time.deltaTime;
            return;
        }

        m_sceneState = LogoSceneState.FadeOut;
        //  �t�F�C�h�C�����J�n����
        m_option.StartSyutterDown(0.5f);
    }

    //  �I�v�V�������J���锻��̎擾
    public override bool NonOptionState()
    {
        //  ��ɊJ���Ȃ�
        return true;
    }
}
