using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleSceneManager : SceneManagement
{
    //  �^�C�g���V�[���̏��
    private enum TitleSceneState
    {
        FadeIn,
        Main,
        FadeOut
    };

    //  �I������
    private enum SelectKind
    {
        Start,
        Option,
        Finish
    }

    [SerializeField, Tooltip("�I�����ڂ̈ʒu")]
    private Transform[] m_selectTransforms;
    [SerializeField, Tooltip("�I���A�C�R���̈ʒu")]
    private Transform m_selectIconTransform;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;
    [SerializeField, Tooltip("BGMAudioSource")]
    private AudioSource m_bgmAudioSource;
    [SerializeField, Tooltip("�A�C�R������")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("����")]
    private AudioClip m_decideAudio;

    [SerializeField, Tooltip("���͎��Ԑ���")]
    private float inputTime = 0.3f;

    //  ���̃V�[��
    const AllScene m_thisScene = AllScene.TitleScene;

    //  �R���g���[���[
    private PlayerControll m_controll;
    //  �ݒ�
    private OptionUI m_option;
    //  �V�[���̏��
    private TitleSceneState m_sceneState;
    //  �I���̎��
    private SelectKind m_selectKind;

    //  ���̓^�C�}�[
    private float m_inputTimer;

    private void Start()
    {
        //  ���͂̐���
        m_controll = new PlayerControll();
        m_controll.Enable();

        //  ����
        m_bgmAudioSource.volume = 0.2f;

        //  �I�v�V�����̐����Ə�����
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        //option = OptionUI.Instance.GetComponent<OptionUI>();
        m_option.Initialized(m_thisScene, m_controll);

        //  �J�n�̏�ɒu��
        SetSelectIcon(SelectKind.Start);

        //  �^�C�}�[�̏�����
        m_inputTimer = 0f;

        //  �t�F�C�h�C����Ԃɂ���
        m_sceneState = TitleSceneState.FadeIn;
        //  �t�F�C�h�C�����J�n����
        m_option.StartSyutterOn(m_fadeTime);
    }

    private void Update()
    {
        //  �I�v�V�������J���Ă��鎞�͏������Ȃ�
        if (OptionUI.m_isOption) return;

        switch(m_sceneState)
        {
            case TitleSceneState.FadeIn:
                //  �t�F�C�h�C���̏I�����擾
                bool flag = m_option.GetFadeFinish();
                //  �I�����Ă��Ȃ�
                if(!flag) break;

                //  �I�������玟�̏�Ԃ�
                m_sceneState = TitleSceneState.Main;
                break;
            case TitleSceneState.Main:
                //  ����
                MainUpdate();
                
                break;
            case TitleSceneState.FadeOut:
                m_bgmAudioSource.volume -= Time.deltaTime * 0.5f;
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
        //  ����{�^�������������̏���
        if (m_controll.Title.Decide.WasPressedThisFrame())
        {
            m_audioSource.PlayOneShot(m_decideAudio);
            //  ��ނ��Ƃɂ����鏈��
            switch(m_selectKind)
            {
                //  �J�n
                case SelectKind.Start:
                    //  �t�F�C�h�A�E�g���J�n
                    m_option.StartSyutterDown(m_fadeTime);
                    //  ��Ԃ��t�F�C�h�A�E�g��
                    m_sceneState = TitleSceneState.FadeOut;
                    break;

                //  �I�v�V����
                case SelectKind.Option:
                    m_option.OpenOption();
                    break;

                //  �I��
                case SelectKind.Finish:
                    //  �Ƃ肠�����m�F�Ȃ��ŏI��������
#if UNITY_EDITOR
                    UnityEditor.EditorApplication.isPlaying = false;//�Q�[���v���C�I��
#else
    Application.Quit();//�Q�[���v���C�I��
#endif
                    break;
            }
            //  �����I��
            return;
        }

        //  �ړ����͂��󂯎��
        float moveY = m_controll.Title.Select.ReadValue<float>();
        //  ���͂����������͏������Ȃ�
        if (Mathf.Abs(moveY) < 0.3f)
        {
            //  �^�C�}�[�̏�����
            m_inputTimer = 0.0f;
            return;
        }

        //  ���͐������Ԃ����炷
        if (m_inputTimer > 0.0f) m_inputTimer -= Time.deltaTime;

        //  ���͂���������"�I��"�ɂ��Ȃ�
        if(moveY < 0f && m_selectKind != SelectKind.Finish && m_inputTimer <= 0f)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            //  ���̑I�����ڂ�
            m_selectKind++;
            //  �I�����ڂ�ݒ�
            SetSelectIcon(m_selectKind);
            //  ���͐������Ԃ�ݒ�
            m_inputTimer = inputTime;
        }
        //  ���͂��������"�J�n"�ɂ��Ȃ�
        else if (moveY > 0f && m_selectKind != SelectKind.Start && m_inputTimer <= 0f)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            //  �O�̑I�����ڂ�
            m_selectKind--;
            //  �I�����ڂ�ݒ�
            SetSelectIcon(m_selectKind);
            //  ���͐������Ԃ�ݒ�
            m_inputTimer = inputTime;
        }
    }
    //  �I�����ڂ̈ʒu��ݒ肷��
    private void SetSelectIcon(SelectKind kind)
    {
        //  �I����Ԃ̕ύX
        m_selectKind = kind;
        //  �ʒu���擾
        Vector3 pos = m_selectIconTransform.position;
        //  �ԍ����擾
        int num = (int)m_selectKind;
        //  Y���W�����ړ�������
        pos.y = m_selectTransforms[num].position.y;
        //  �ʒu��ݒ�
        m_selectIconTransform.position = pos;
    }

    //  �I�v�V�������J���锻��̎擾
    public override bool NonOptionState()
    {
        //  �t�F�C�h���͊J���Ȃ�
        if (m_sceneState != TitleSceneState.Main) return true;
        return false;
    }
}
