using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public enum PlaySceneState
{
    FadeIn,         //  �t�F�C�h�C��
    StartBefore,    //  �n�܂�O
    Playing,        //  �v���C��
    GameOver,       //  �Q�[���I�[�o�[
    Clear,          //  �N���A
    FadeOut          //  �t�F�C�h�A�E�g
};

public class PlaySceneManager : SceneManagement
{
    //  �v���C�V�[���̏��
    public static PlaySceneState m_sceneState = PlaySceneState.StartBefore;

    [SerializeField, Header("�T�E���h���Ǘ�����N���X")]
    private SoundManager m_soundManager;
    [SerializeField, Header("UI���Ǘ�����N���X")]
    private UIManager m_uiManager;
    [SerializeField, Header("�v���C���[")]
    private PlayerController m_player;
    [SerializeField, Header("�S�[��")]
    private Goal m_goal;
    [SerializeField, Header("�`�F�b�N�|�C���g")]
    private CheckPoint[] m_checkPoints;
    [SerializeField, Header("���W�e�[�v")]
    private Tape[] m_tapes;
    [SerializeField, Tooltip("�S�[���G�t�F�N�g")]
    private ParticleSystem m_clear;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;

    //  �v���C���[�̊J�n�ʒu
    private Vector3 m_startPos;
    //  ���̃V�[���̖��O
    private string m_nextName;
    //  �N���A����
    private float m_clearTimer;
    //  �v���C�M�~�b�N
    private PlayGimmick[] m_playGimmicks;
    //  ���W���̉���t���O
    private bool[] m_tapeFlags;
    //  ���W���̐�
    private int m_tapeNum;

    //  ����
    private PlayerControll m_inputActions;
    //  �I�v�V����UI
    private OptionUI m_option;

    //  �萔  //////////////////////////////////////////////////////////////////////////////////////////////
    //  �V�[��ID�i�v���C�V�[���j
    private const AllScene PLAYSCENE = AllScene.PlayScene;

    //  �X�^�[�g
    private void Start()
    {
        //  ��U���̃X�e�[�W�̖��O���i�[���Ă���
        m_nextName = m_nextSceneNames[0];

        //  ���͂��󂯎��
        m_inputActions = new PlayerControll();
        //  ����ON
        m_inputActions.Enable();

        //  �I�v�V�����̐����Ə�����
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        //  �I�v�V����������������
        m_option.Initialized(PLAYSCENE, m_inputActions);

        //  SoundManager�̏�����
        m_soundManager.SoundManagerInit(m_player.transform);
        //  UIManager�̏�����
        m_uiManager.UIManagerInit(m_player.gameObject.GetComponent<PlayerHaveSound>(), m_inputActions);

        //  �v���C���[�̊J�n�ʒu���L�^
        m_startPos = m_player.transform.position;
        //  �v���C���[�̏�����
        m_player.Init(m_inputActions);
        //  �v���C���[�̔�A�N�e�B�u
        m_player.gameObject.SetActive(false);

        //  �`�F�b�N�|�C���g���m��n��
        for (int i = 0; i < m_checkPoints.Length; i++)
        {
            for (int j = 0; j < m_checkPoints.Length; j++)
            {
                //  �����Ȃ珈�����Ȃ�
                if (m_checkPoints[i] == m_checkPoints[j]) continue;

                m_checkPoints[i].AddCheckPoint(m_checkPoints[j]);
            }
        }

        //  PlayGimmick�����ׂĎ擾
        m_playGimmicks = GameObject.FindObjectsOfType<PlayGimmick>();

        //  ������
        m_tapeFlags = new bool[m_tapes.Length];
        TapeFlagReset();

        //  �^�C�}�[�̏�����
        m_clearTimer = 0f;
        m_clear.gameObject.SetActive(false);

        m_audioSource.Play();

        //  ��Ԃ�'�t�F�C�h�C��'
        m_sceneState = PlaySceneState.FadeIn;
        //  �t�F�C�h�C�����J�n����
        m_option.StartSyutterOn(m_fadeTime);
    }

    //  �X�V
    private void Update()
    {
        //  �I�v�V�������J���Ă��鎞�͏������Ȃ�
        if (OptionUI.m_isOption)
        {
            m_uiManager.Non();
            return;
        }

        //  SoundManager�̍X�V
        m_soundManager.SoundManagerUpdate();

        //  �V�[���̏�Ԃɂ�鏈��
        switch (m_sceneState)
        {
            //  �t�F�C�h�C��
            case PlaySceneState.FadeIn:
                //  �t�F�C�h�C���̏I����������
                bool flag = m_option.GetFadeFinish();
                //  �I�����Ă��Ȃ��Ȃ珈�����Ȃ�
                if (!flag) return;

                //  �J�n�O��
                m_sceneState = PlaySceneState.StartBefore;
                //  �v���C���[��\��
                m_player.gameObject.SetActive(true);
                //uiManager.FadeInStart();
                break;

            //  �J�n�O
            case PlaySceneState.StartBefore:

                //  �J�n�̔�������
                bool startFlag = m_player.GetIsStart();
                //  �X�|�[���A�j���[�V�������I�����Ă��Ȃ��Ȃ珈�����Ȃ�
                if (!startFlag) return;

                //  ��Ԃ�'�v���C��'��
                m_sceneState = PlaySceneState.Playing;
                break;

            case PlaySceneState.Playing:
                m_uiManager.On();
                //  �S�[������(��������x�I��点��)���S�[�������Ƃ��̏�����Goal()���ɋL�q
                if (IsGoal()) return;

                //  ���Ԃ�ǉ�����
                m_clearTimer += Time.deltaTime;
                //  ���W�A�C�e���̎擾
                for (int i = 0; i < m_tapes.Length; i++)
                {
                    if (!m_tapes[i].GetSetTape) continue;

                    //  ��\��
                    m_tapes[i].GetSetTape = false;
                    m_tapes[i].gameObject.SetActive(false);
                    //  �擾���
                    m_tapeFlags[m_tapeNum] = true;
                    //  UI��ݒ�
                    m_uiManager.SetTapeUI(m_tapeFlags);
                    m_tapeNum++;
                }

                //  �Q�[���I�[�o�[����(��������x�I��点��)���Q�[���I�[�o�[�����Ƃ��̏�����IsGameOver()���ɋL�q
                if (IsGameOver()) return;

                //  UIManager�̍X�V�iRestart�j
                if (m_uiManager.UIUpdate())
                {
                    m_sceneState = PlaySceneState.GameOver;
                    //  �t�F�C�h�J�n
                    m_uiManager.FadeOutStart();
                    return;
                }
                break;

            case PlaySceneState.GameOver:
                //  �����F�Ó]���鎞�Ԃ��l�����Ă��Ȃ����l������ꍇ�A�j���[�V�������ŌĂяo���֐��̃^�C�~���O��ς���
                if(m_uiManager.ReStart())
                {
                    //  ���X�^�[�g
                    ReStart();
                    //  ��Ԃ�߂�
                    m_sceneState = PlaySceneState.StartBefore;

                    m_uiManager.FadeInStart();
                }
                break;

            case PlaySceneState.Clear:
                //  �v���C���[�̃N���A�X�V
                m_player.PlayerClear();
                //  UIManager�̍X�V
                bool decide = m_uiManager.ClearUIUpdate();
                //  ���肵�Ă��Ȃ�
                if (!decide) return;

                //  ���肵���ԍ����擾
                int selectNum = m_uiManager.ClearUISelectNumber();
                //  �ԍ��ɂ�鏈��
                AfterClearUpdate((ClearSelect)selectNum);
                break;

            case PlaySceneState.FadeOut:
                flag = m_option.GetFadeFinish();
                if (flag)
                {
                    m_option.Finish();
                    SceneManager.LoadScene(m_nextName);
                }
                break;
        }
    }

    //  ���̍Đ�
    private void PlayAudio()
    {
        m_audioSource.Play();
    }

    //  �S�[������
    private bool IsGoal()
    {
        //  �S�[���������擾
        bool goalFlag = m_goal.GetSetIsGoal;
        //  �S�[�����ĂȂ�Ώ������Ȃ�
        if (!goalFlag) return false;

        //  ��Ԃ��N���A��
        m_sceneState = PlaySceneState.Clear;
        m_audioSource.Stop();
        Invoke("PlayAudio", 5.0f);
        m_uiManager.Non();
        //  �N���AUI��\��
        m_uiManager.Clear(m_clearTimer, m_tapeNum);
        m_clear.gameObject.SetActive(true);
        m_clear.Play();
        m_player.PlayerClearInit(m_goal.transform.position);
        return true;
    }

    //  �Q�[���I�[�o�[����
    private bool IsGameOver()
    {
        //  �Q�[���I�[�o�[�������擾
        bool gameOverFlag = m_player.GetIsGameOver();
        //  �Q�[���I�[�o�[���ĂȂ�Ώ������Ȃ�
        if (!gameOverFlag) return false;
        
        //  ��Ԃ�'�Q�[���I�[�o�['��
        m_sceneState = PlaySceneState.GameOver;

        //  �t�F�C�h�J�n
        m_uiManager.FadeOutStart();

        return true;
    }

    //  �N���A�㏈��
    private void AfterClearUpdate(ClearSelect clearSelect)
    {
        m_clear.gameObject.SetActive(false);
        CancelInvoke();
        switch (clearSelect)
        {
            //  �X�e�[�W�Z���N�g�ɖ߂�
            case ClearSelect.Back:
                m_nextName = m_nextSceneNames[0];

                NextScene();
                break;

            //  ������x�����X�e�[�W��Play
            case ClearSelect.ReStart:
                //  ���Z�b�g
                ClearReset();
                //  ��Ԃ�߂�
                m_sceneState = PlaySceneState.GameOver;
                m_uiManager.FadeOutStart();
                break;

            //  ���̃X�e�[�W��
            case ClearSelect.Next:
                m_nextName = m_nextSceneNames[1];

                NextScene();
                break;
        }
    }

    //  ���X�^�[�g
    private void ReStart()
    {
        //  �v���C���[�̈ʒu��߂�
        PlayerReset(true);
        //  �v���C�M�~�b�N�����Z�b�g
        PlayGimmickReset();
    }

    //  ���Z�b�g
    private void ClearReset()
    {
        //  �v���C���[���ŏ�����
        PlayerReset(false);
        //  �v���C�M�~�b�N�����Z�b�g
        PlayGimmickReset();
        m_audioSource.Play();
        m_uiManager.On();
        //  ���Ԃ����Z�b�g
        m_clearTimer = 0f;
        //  �S�Ẵ`�F�b�N�|�C���g�����Z�b�g
        if(m_checkPoints != null)
        {
            for (int i = 0; i < m_checkPoints.Length; i++)
            {
                //  �S��false��
                m_checkPoints[i].GetSetCheck = false;
                //  �A�j���[�^��false�ōĐ�
                m_checkPoints[i].CheckAnimator(false);
            }
        }
        //  �S�[����false
        m_goal.GetSetIsGoal = false;
        //  ���U���g���\��
        m_uiManager.ClearReset();
    }

    //  �v���C���[���Z�b�g
    private void PlayerReset(bool checkpoint)
    {
        //  �ŏ����疔�̓`�F�b�N�|�C���g�����݂��Ȃ�
        if (!checkpoint || m_checkPoints == null)
        {
            m_player.PlayerReset(m_startPos);
            return;
        }

        //  �`�F�b�N�|�C���g����
        //  �v���C���[�̈ʒu��߂�

        bool flag = false;

        for (int i = 0; i < m_checkPoints.Length; i++)
        {
            flag = m_checkPoints[i].GetSetCheck;
            if (!flag) continue;

            //  true�̃`�F�b�N�|�C���g����
            m_player.PlayerReset(m_checkPoints[i].transform.position);
            break;
        }
        //  �`�F�b�N�|�C���g������ʂ��ĂȂ���΍ŏ�����
        if (!flag) m_player.PlayerReset(m_startPos);
    }

    //  �v���C�M�~�b�N���Z�b�g
    private void PlayGimmickReset()
    {
        //  ��������
        for (int i = 0; i < m_playGimmicks.Length; i++)
        {
            //  ��\���ɂȂ��Ă�����͕̂\�����Ȃ���
            if (!m_playGimmicks[i].gameObject.activeSelf) m_playGimmicks[i].gameObject.SetActive(true);
            //  ���Z�b�g����
            m_playGimmicks[i].GetComponent<PlayGimmick>().GimmickReset();
        }
    }

    //  ���W���̃��Z�b�g
    private void TapeFlagReset()
    {
        for (int i = 0; i < m_tapes.Length; i++)
        {
            m_tapes[i].gameObject.SetActive(true);
            m_tapeFlags[i] = false;
        }

        m_tapeNum = 0;
    }

    //  �I�v�V�������J���锻��̎擾
    public override bool NonOptionState()
    {
        //  �v���C���ȊO�͊J���Ȃ�
        if (m_sceneState != PlaySceneState.Playing) return true;
        return false;
    }

    //  ���̃V�[��
    private void NextScene()
    {
        m_option.StartSyutterDown(m_fadeTime);
        //  ��Ԃ�'�J�n�O'
        m_sceneState = PlaySceneState.FadeOut;
    }
}
