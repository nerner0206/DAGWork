using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SelectStageManager : SceneManagement
{
    //  �Z���N�g�V�[���̏��
    private enum SelectStageState
    {
        FadeIn,
        Main,
        FadeOut
    };

    [SerializeField, Header("�}�b�v�̗v�f")]
    private Map[] m_maps;
    [SerializeField, Header("�}�b�v�A�C�R���̈ʒu")]
    private Transform m_iconTransform;
    [SerializeField, Header("�}�b�v�A�C�R���̈ړ���")]
    private Transform[] m_iconMoves;
    [SerializeField, Header("�I��UI")]
    private SelectUI m_selectUI;

    [SerializeField, Tooltip("�A�C�R�����쉹")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("���艹")]
    private AudioClip m_decideAudio;
    [SerializeField, Tooltip("AudioSource")]
    private AudioSource audioSource;
    [SerializeField, Tooltip("BGMAudioSource")]
    private AudioSource bgmAudioSource;

    [SerializeField, Tooltip("���͎��Ԑ���")]
    private float inputTime = 0.3f;

    //  �R���g���[���[
    private PlayerControll m_controll;
    //  ���̃V�[��
    const AllScene m_thisScene = AllScene.SelectScene;
    //  �ݒ�
    private OptionUI m_option;
    //  �V�[���̏��
    private SelectStageState m_sceneState;
    //  �I�����ԍ�
    private int m_mapNum;

    //  ���̓^�C�}�[
    private float m_inputTimer;
    //  ���̃V�[��
    private string m_nextScene;

    //  �������ʂ̒萔
    const float INIT_BGM_VOLUME = 0.2f;

    //  ������
    private void Start()
    {
        m_nextScene = m_nextSceneNames[0];

        //  ���͂̐���
        m_controll = new PlayerControll();
        m_controll.Enable();

        //  �I�v�V�����̐����Ə�����
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        m_option.Initialized(m_thisScene, m_controll);

        //  �ŏ��̈ʒu
        m_mapNum = 0;
        //  �A�C�R���̈ʒu��ύX
        SetIconPos(m_mapNum);
        //  UI�̐ݒ�
        m_selectUI.SetUI(m_mapNum);

        //  �^�C�}�[�̏�����
        m_inputTimer = 0f;

        //  ����
        bgmAudioSource.volume = INIT_BGM_VOLUME;

        //  �t�F�C�h�C����Ԃɂ���
        m_sceneState = SelectStageState.FadeIn;
        //  �t�F�C�h�C�����J�n����
        m_option.StartSyutterOn(m_fadeTime);
    }
    //  �X�V����
    private void Update()
    {
        //  �I�v�V�������J���Ă��鎞�͏������Ȃ�
        if (OptionUI.m_isOption) return;

        switch (m_sceneState)
        {
            case SelectStageState.FadeIn:
                //  �t�F�C�h�C���̏I�����擾
                bool flag = m_option.GetFadeFinish();
                //  �I�����Ă��Ȃ�
                if (!flag) break;

                //  �I�������玟�̏�Ԃ�
                m_sceneState = SelectStageState.Main;
                break;
            case SelectStageState.Main:
                //  ����
                MainUpdate();

                break;
            case SelectStageState.FadeOut:
                bgmAudioSource.volume -= Time.deltaTime;
                //  �t�F�C�h�A�E�g�̏I�����󂯎��
                flag = m_option.GetFadeFinish();

                if (!flag) break;

                //  �I�v�V�����̉�ʑJ�ڏ���
                m_option.Finish();
                //  �Z���N�g�V�[���ֈړ�����
                SceneManager.LoadScene(m_nextScene);
                break;
        }
    }

    private void MainUpdate()
    {
        //  ����{�^���������ꂽ��
        if(m_controll.Select.Decide.WasPressedThisFrame())
        {
            audioSource.PlayOneShot(m_decideAudio);
            m_nextScene = m_nextSceneNames[m_mapNum];
            //  �t�F�C�h�A�E�g���J�n
            m_option.StartSyutterDown(m_fadeTime);
            //  ��Ԃ��t�F�C�h�A�E�g��
            m_sceneState = SelectStageState.FadeOut;
            //  �����I��
            return;
        }

        //  �o�b�N�{�^���������ꂽ��
        if (m_controll.Option.Back.WasPressedThisFrame() && !m_option.GetInputWait())
        {
            //  �^�C�g���V�[��
            m_nextScene = "TitleScene";

            //  �t�F�C�h�A�E�g���J�n
            m_option.StartSyutterDown(m_fadeTime);
            //  ��Ԃ��t�F�C�h�A�E�g��
            m_sceneState = SelectStageState.FadeOut;
            //  �����I��
            return;
        }

        //  �ړ����͂��󂯎��
        float moveX = m_controll.Select.MoveX.ReadValue<float>();
        //  ���͂����������͏������Ȃ�
        if (Mathf.Abs(moveX) < 0.3f)
        {
            //  �^�C�}�[�̏�����
            m_inputTimer = 0.0f;
            return;
        }

        //  ���͐������Ԃ����炷
        if (m_inputTimer > 0.0f) m_inputTimer -= Time.deltaTime;

        //  ���͂���������"�I��"�ɂ��Ȃ�
        if (moveX > 0f && m_inputTimer <= 0f)
        {
            audioSource.PlayOneShot(m_moveAudio);
            //  ���̑I�����ڂ�
            m_mapNum++;
            //  �ő吔�𒴂�����
            if (m_mapNum > m_maps.Length - 1) m_mapNum = 0;
            //  �I�����ڂ�ݒ�
            SetIconPos(m_mapNum);
            //  UI��ݒ�
            m_selectUI.SetUI(m_mapNum);
            //  ���͐������Ԃ�ݒ�
            m_inputTimer = inputTime;
        }
        //  ���͂��������"�J�n"�ɂ��Ȃ�
        else if (moveX < 0f && m_inputTimer <= 0f)
        {
            audioSource.PlayOneShot(m_moveAudio);
            //  �O�̑I�����ڂ�
            m_mapNum--;
            //  �Œᐔ�𒴂�����
            if (m_mapNum < 0) m_mapNum = m_maps.Length - 1;
            //  �I�����ڂ�ݒ�
            SetIconPos(m_mapNum);
            //  UI��ݒ�
            m_selectUI.SetUI(m_mapNum);
            //  ���͐������Ԃ�ݒ�
            m_inputTimer = inputTime;
        }
    }

    private void SetIconPos(int num)
    {
        //  �ԍ��̈ʒu���擾
        Vector3 pos = m_iconMoves[num].transform.position;
        //  �ʒu��ύX
        m_iconTransform.position = pos;

        //  �}�b�v�}�e���A���̕ύX
        for (int i = 0; i < m_maps.Length; i++)
        {
            //  �A�C�R����̃}�b�v�̃}�e���A���̂�
            if (i == num)
            {
                m_maps[i].SetOnIcon();
                continue;
            }

            //  ����ȊO
            m_maps[i].SetRemoveIcon();
        }
    }

    //  �I�v�V�������J���锻��̎擾
    public override bool NonOptionState()
    {
        //  �t�F�C�h���͊J���Ȃ�
        if (m_sceneState != SelectStageState.Main) return true;
        return false;
    }
}
