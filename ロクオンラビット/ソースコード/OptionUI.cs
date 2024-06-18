using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.Audio;
using DG.Tweening;

public enum OptionSelect
{
    BGM,
    SE,
    StageSelect,
    End,

    Null
};

[RequireComponent(typeof(Canvas))]
[RequireComponent(typeof(CanvasScaler))]
[RequireComponent(typeof(GraphicRaycaster))]
public class OptionUI : MonoBehaviour
{
    //  ���̃I�u�W�F�N�g���i�[����
    private static GameObject m_instance;
    //  ���̃I�u�W�F�N�g��n��
    public static GameObject GetInstance { get { return m_instance; } }

    //  Option��
    public static bool m_isOption = false;

    [SerializeField, Tooltip("AudioMixer")]
    private AudioMixer m_audioMixer;

    [SerializeField, Tooltip("�w�i�v���n�u")]
    private GameObject m_backImagePrefab;

    [SerializeField, Tooltip("�X�e�B�b�N�̃f�b�h�]�[��")]
    private float m_deadZone = 0.1f;

    [SerializeField, Tooltip("���͂̃N�[���^�C��")]
    private float m_coolTime = 0.5f;

    [SerializeField, Tooltip("�m�F��ʃv���n�u")] 
    private GameObject m_confirmationPrefab;

    [SerializeField, Tooltip("�ԍ�")]
    private Sprite[] m_numImages;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;
    [SerializeField, Tooltip("�J�[�\���ړ���")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("���艹")]
    private AudioClip m_decideAudio;
    [SerializeField, Tooltip("�V���b�^�[���鉹")]
    private AudioClip m_downClipAudio;

    //  ����
    private PlayerControll m_inputActions;
    //  ���݂̃V�[��
    private AllScene m_nowScene;

    //  �V�[���̃}�l�[�W���[���擾����
    private SceneManagement m_sceneManager;
    
    //  �w�i�I�u�W�F�N�g
    private GameObject m_backImage;
    //  �|�[�Y�^�C�g���I�u�W�F�N�g
    private GameObject m_pauseTitle;
    //  �I���I�u�W�F�N�g
    private GameObject[] m_selectObjs;
    //  �I���摜
    private Image[] m_selectImages;
    //  �A�C�R���I�u�W�F�N�g
    private GameObject m_selectIcon;
    //  �A�C�R�����W
    private Vector3[] m_iconPoses;
    //  �I���A�C�R���摜
    private Image m_selectIconImage;
    //  �I��ԍ�
    private int m_selectNum;
    
    //  �^�C�}�[
    private float m_timer;

    //  �m�F��ʃI�u�W�F�N�g
    private GameObject m_confirmation;
    //  Yes/No�I�u�W�F�N�g
    private GameObject[] m_YNSelectObjs;
    //  Yes/No�I��ԍ�
    private int m_YNnum;

    //  �I�v�V�����̑I���N���X
    private OptionSelect m_optionSelect;

    //  ���a
    private float m_radian;

    //  BGM�̉���
    private int m_bgmVol;
    //  SE�̉���
    private int m_seVol;
    //  BGM�̉��ʉ摜
    private Image m_bgmVolImage;
    //  SE�̉��ʉ摜
    private Image m_seVolImage;

    //  ���̓^�C�}�[
    private float m_inputTimer;
    //  ���͑ҋ@
    private bool m_inputWait;

    /// <summary>
    /// �t�F�C�h�C��/�A�E�g�p
    /// </summary>
    [SerializeField, Tooltip("�t�F�C�h�p�p�l��")] 
    private GameObject m_panelPrefab;

    //  �t�F�C�h�摜
    private Image m_fadeImage;
    //  �t�F�C�h�I��
    private bool m_fadeFinish;

    public void Init()
    {
        //  �擾
        if (m_instance == null)
        {
            DontDestroyOnLoad(gameObject);
            m_instance = gameObject;
        }
        else
        {
            Destroy(gameObject);
        }

        ////  Canvas�̏����ݒ�  //////////////////////////////////////////////////////////////////////////////////////////////////////

        //  canvas�̐ݒ�
        gameObject.GetComponent<Canvas>().renderMode = RenderMode.ScreenSpaceOverlay;
        gameObject.GetComponent<Canvas>().sortingOrder = 1000;
        //  CanvasScaler�̐ݒ�
        gameObject.GetComponent<CanvasScaler>().uiScaleMode = CanvasScaler.ScaleMode.ScaleWithScreenSize;
        gameObject.GetComponent<CanvasScaler>().referenceResolution = new Vector2(1920, 1080);

        GameObject man = GameObject.FindGameObjectWithTag("Manager");
        m_sceneManager = man.GetComponent<SceneManagement>();

        m_optionSelect = OptionSelect.Null;

        ////  UI�𐶐�  ////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

        //  �������
        //  �q�I�u�W�F�N�g�𐶐�
        m_backImage = Instantiate(m_backImagePrefab, gameObject.transform);
        //  �ʒu�����
        m_backImage.transform.localPosition = new Vector3(0.0f, 1080.0f, 0.0f);
        //  ��\��
        m_backImage.SetActive(false);
        m_pauseTitle = m_backImage.transform.GetChild(0).gameObject;
        //  �q�I�u�W�F�N�g�̐�
        int n = m_pauseTitle.transform.childCount;
        //  ������
        m_selectObjs = new GameObject[(int)OptionSelect.Null];
        m_selectImages = new Image[(int)OptionSelect.Null];

        m_iconPoses = new Vector3[(int)OptionSelect.Null];
        m_iconPoses[0] = Vector3.zero;
        m_iconPoses[1] = new Vector3(0.0f, -160.0f, 0.0f);
        m_iconPoses[2] = new Vector3(150.0f, -300.0f, 0.0f);
        m_iconPoses[3] = new Vector3(150.0f, -440.0f, 0.0f);

        m_inputWait = false;

        for (int i = 0; i < (int)OptionSelect.Null; i++)
        {
            m_selectObjs[i] = m_pauseTitle.transform.GetChild(i).gameObject;
            m_selectImages[i] = m_selectObjs[i].GetComponent<Image>();
        }
        //  �A�C�R�����擾
        m_selectIcon = m_pauseTitle.transform.GetChild(n - 1).gameObject;
        //  �A�C�R���̐F���擾
        m_selectIconImage = m_selectIcon.GetComponent<Image>();

        m_selectNum = 0;

        m_selectIcon.transform.localPosition = m_iconPoses[m_selectNum];

        //  �m�F���
        //  �q�I�u�W�F�N�g�𐶐�
        m_confirmation = m_pauseTitle.transform.GetChild(n - 2).gameObject;
        //  ��\��
        m_confirmation.SetActive(false);

        //  �I�u�W�F�N�g���擾
        m_YNSelectObjs = new GameObject[2];
        m_YNSelectObjs[0] = m_confirmation.transform.GetChild(0).gameObject;
        m_YNSelectObjs[1] = m_confirmation.transform.GetChild(1).gameObject;
        m_YNnum = 0;

        m_radian = 0.0f;

        m_bgmVolImage = m_selectObjs[0].transform.GetChild(1).gameObject.GetComponent<Image>();
        m_seVolImage = m_selectObjs[1].transform.GetChild(1).gameObject.GetComponent<Image>();

        m_bgmVol = 5;
        m_seVol = 7;
        m_bgmVolImage.sprite = m_numImages[m_bgmVol];
        m_seVolImage.sprite = m_numImages[m_seVol];
        SetAudioMixerBGM((float)m_bgmVol / 9.0f);
        SetAudioMixerSE((m_seVol) / 9.0f);

        m_inputTimer = 0.0f;

        //  ����
        GameObject fade = Instantiate(m_panelPrefab, gameObject.transform);
        //  Image�擾
        m_fadeImage = fade.GetComponent<Image>();
        //  ��\��
        fade.SetActive(true);
    }
    // Update is called once per frame
    private void Update()
    {
        if (m_sceneManager == null) return;
        //  �I�v�V�������J���Ȃ����
        if (m_sceneManager.NonOptionState()) return;
        //  ���͂��󂯎��(�^�C�g���V�[���͗�O)
        if (m_inputActions.Option.Option.WasPressedThisFrame() && m_nowScene != AllScene.TitleScene)
        {
            //  �܂��I�v�V�������J���Ă��Ȃ�
            if(!m_isOption)
            {
                OpenOption();
            }
            //  ���ɃI�v�V�������J���Ă���
            else
            {
                ExitOption();
            }
            return;
        }

        //  �I�v�V�������J���Ă��Ȃ���Ώ������Ȃ�
        if (!m_isOption) return;

        switch(m_optionSelect)
        {
            case OptionSelect.BGM:
                //  �X���C�_�[�𓮂���
                SliderMove(ref m_bgmVol, ref m_bgmVolImage);
                SetAudioMixerBGM((float)m_bgmVol / 9.0f);
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  �F��߂�
                    BackColor();

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.SE:
                //  �X���C�_�[�𓮂���
                SliderMove(ref m_seVol, ref m_seVolImage);
                SetAudioMixerSE((m_seVol) / 9.0f);
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  �F��߂�
                    BackColor();

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.StageSelect:
                //  �X�V
                YNSelect();
                //  ����
                if(m_inputActions.Option.Decide.WasPressedThisFrame())
                {
                    m_audioSource.PlayOneShot(m_decideAudio);
                    //  �~
                    if (m_YNnum == 0)
                    {
                        //  �F��߂�
                        BackColor();
                        //  �m�F��ʂ��\��
                        m_confirmation.SetActive(false);

                        m_optionSelect = OptionSelect.Null;
                    }
                    //  �Z
                    else
                    {
                        //  �I�v�V���������
                        CloseOption();
                        //  �V���b�^�[�����܂Œ��ߐ؂�
                        //  �V�[���J��
                        var doT = DOTween.Sequence()
                            .Append(m_backImage.transform.DOLocalMoveY(0.0f, 0.2f))
                            .AppendCallback(() => SceneManager.LoadScene("SelectStage"));
                    }
                }
                
                //  �߂�
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  �F��߂�
                    BackColor();
                    //  �m�F��ʂ��\��
                    m_confirmation.SetActive(false);

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.End:
                //  �X�V
                YNSelect();
                //  ����
                if (m_inputActions.Option.Decide.WasPressedThisFrame())
                {
                    m_audioSource.PlayOneShot(m_decideAudio);
                    //  �~
                    if (m_YNnum == 0)
                    {
                        //  �F��߂�
                        BackColor();
                        //  �m�F��ʂ��\��
                        m_confirmation.SetActive(false);

                        m_optionSelect = OptionSelect.Null;
                    }
                    //  �Z
                    else
                    {
#if UNITY_EDITOR
                        UnityEditor.EditorApplication.isPlaying = false;//�Q�[���v���C�I��
#else
    Application.Quit();//�Q�[���v���C�I��
#endif
                    }
                }
                //  �߂�
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  �F��߂�
                    BackColor();
                    //  �m�F��ʂ��\��
                    m_confirmation.SetActive(false);

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.Null:
                //  �I�v�V������I��
                OptionSelectUpdate();
                break;
        }
    }
    private void SliderMove(ref int num, ref Image image)
    {
        float m = m_inputActions.Option.MoveX.ReadValue<float>();

        if (Mathf.Abs(m) < m_deadZone)
        {
            m_inputTimer = -1.0f;
            return;
        }
        if (m_inputTimer >= 0.0f)
        {
            m_inputTimer -= Time.deltaTime;
            return;
        }
        
        if (m > 0f && num < 9 && m_inputTimer < 0.0f) 
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            num++;
            image.sprite = m_numImages[num];
            m_inputTimer = 0.5f;
        }
        else if(m < 0f && num > 0 && m_inputTimer < 0.0f)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            num--;
            image.sprite = m_numImages[num];
            m_inputTimer = 0.5f;
        }
    }
    public void OpenOption()
    {
        //  �I�v�V�������J��
        m_isOption = true;
        //  �V���b�^�[�̈ʒu����ɂ���
        m_backImage.transform.localPosition = new Vector3(0.0f, 1080.0f, 0.0f);
        //  �\��
        m_backImage.SetActive(true);
        //  UI���\��
        m_pauseTitle.SetActive(true);
        m_pauseTitle.transform.localPosition = new Vector3(0.0f, -225.0f, 0.0f);
        //  ���Ɍ�����
        m_backImage.transform.DOLocalMoveY(200.0f, 0.3f).SetEase(Ease.Linear);

        m_selectNum = 0;
        m_selectIcon.transform.localPosition = m_iconPoses[m_selectNum];

        //  �v���C�V�[���ȊO�Ȃ�Z���N�g�V�[���ɖ߂�𔼓����i�I��s�\�j
        if (m_nowScene == AllScene.PlayScene) return;

        //  �������ɂ���
        Color color = m_selectImages[(int)OptionSelect.StageSelect].color;
        color.a = 0.5f;
        m_selectImages[(int)OptionSelect.StageSelect].color = color;
    }
    private void CloseOption()
    {
        //  �I�v�V���������
        m_isOption = false;
        m_pauseTitle.SetActive(false);

        //  �F��߂�
        Color color = m_selectImages[(int)OptionSelect.StageSelect].color;
        color.a = 1.0f;
        m_selectImages[(int)OptionSelect.StageSelect].color = color;

        //  �A�C�R���̐F��ς���
        BackColor();
        //  �I����������
        m_optionSelect = OptionSelect.Null;

        //  �m�F��ʔ�\��
        m_confirmation.SetActive(false);
    }
    private void BackColor()
    {
        //  �F��ς���
        Color color = m_selectIconImage.color;
        color.r = 0f;
        color.b = 1f;
        m_selectIconImage.color = color;
    }
    private void YNSelect()
    {
        //  �T�C�Y�ύX
        m_YNSelectObjs[m_YNnum].transform.localScale = Vector3.one + (new Vector3(0.05f, 0.05f, 0.0f) * Mathf.Sin(m_radian));
        m_radian += Mathf.PI / 180.0f;

        //  ����
        float moveX = m_inputActions.Option.MoveX.ReadValue<float>();
        if (Mathf.Abs(moveX) < m_deadZone) return;

        //  �ʒu��ς���
        if (moveX > 0f && m_YNnum != 0)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            m_YNnum = 0;
            m_YNSelectObjs[1].transform.localScale = Vector3.one;
            m_radian = 0.0f;
        }
        else if (moveX < 0f && m_YNnum != 1)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            m_YNnum = 1;
            m_YNSelectObjs[0].transform.localScale = Vector3.one;
            m_radian = 0.0f;
        }
    }

    public void Initialized(AllScene scene, PlayerControll con)
    {
        m_inputActions = con;

        GameObject man = GameObject.FindGameObjectWithTag("Manager");
        m_sceneManager = man.GetComponent<SceneManagement>();

        m_nowScene = scene;
    }
    public void Finish()
    {
        m_sceneManager = null;
    }
    //  �I�v�V��������ʂł̍X�V����
    public void OptionSelectUpdate()
    {
        //  �߂�
        if(m_inputActions.Option.Back.WasPressedThisFrame())
        {
            //  �V���b�^�[���オ��
            ExitOption();
            return;
        }
        //  �I��
        if (m_inputActions.Option.Decide.WasPressedThisFrame())
        {
            m_audioSource.PlayOneShot(m_decideAudio);
            //  �F��ς���
            Color color = m_selectIconImage.color;
            color.r = 1f;
            color.b = 0f;
            m_selectIconImage.color = color;

            switch ((OptionSelect)m_selectNum)
            {

                case OptionSelect.BGM:
                    //  BGM�����
                    m_optionSelect = OptionSelect.BGM;
                    break;
                case OptionSelect.SE:
                    //  SE�����
                    m_optionSelect = OptionSelect.SE;
                    break;
                case OptionSelect.StageSelect:
                    //  �X�e�[�W�Z���N�g�m�F
                    m_optionSelect = OptionSelect.StageSelect;
                    //  �m�F�{�^���̈ʒu
                    m_confirmation.transform.localPosition = Vector3.zero;
                    //  �߂邩�m�F
                    m_confirmation.SetActive(true);
                    //  �I�����~
                    m_YNnum = 0;
                    break;
                case OptionSelect.End:
                    //  �I���m�F
                    m_optionSelect = OptionSelect.End;
                    //  �m�F�{�^���̈ʒu
                    m_confirmation.transform.localPosition = new Vector3(0.0f, -130.0f, 0.0f);
                    //  �I�����邩�m�F
                    m_confirmation.SetActive(true);
                    //  �I�����~
                    m_YNnum = 0;
                    break;
            }
            return;
        }

        float move = m_inputActions.Option.MoveY.ReadValue<float>();

        //  ���͂��Ȃ�
        if (Mathf.Abs(move) < m_deadZone)
        {
            m_timer = 0f;
            return;
        }
        //  ���͂̃N�[���^�C��������
        if (m_timer > 0f)
        {
            m_timer -= Time.deltaTime;
            return;
        }

        m_audioSource.PlayOneShot(m_moveAudio);

        //  ������
        if (move > 0f)
        {
            m_selectNum++;
            //  �v���C�V�[���ł͂Ȃ��Ȃ��΂�
            if (m_nowScene != AllScene.PlayScene && (OptionSelect)m_selectNum == OptionSelect.StageSelect) m_selectNum++;
        }
        //  �����
        else
        {
            m_selectNum--;
            //  �v���C�V�[���ł͂Ȃ��Ȃ��΂�
            if (m_nowScene != AllScene.PlayScene && (OptionSelect)m_selectNum == OptionSelect.StageSelect) m_selectNum--;
        }

        //  �I��l�͈̔�
        if (m_selectNum > (int)OptionSelect.End) m_selectNum = (int)OptionSelect.End;
        else if (m_selectNum < (int)OptionSelect.BGM) m_selectNum = (int)OptionSelect.BGM;

        //  ���ۂɃA�C�R���𓮂���
        m_selectIcon.transform.localPosition = m_iconPoses[m_selectNum];

        //  �N�[���^�C��
        m_timer = m_coolTime;
    }
    //BGM
    public void SetAudioMixerBGM(float value)
    {
        //  -80~20�̊�
        var volume = Mathf.Lerp(-80f, 20f, value);
        //audioMixer�ɑ��
        m_audioMixer.SetFloat("BGMVol", volume);
    }
    //SE
    public void SetAudioMixerSE(float value)
    {
        //  -80~20�̊�
        var volume = Mathf.Lerp(-80f, 20f, value);
        //audioMixer�ɑ��
        m_audioMixer.SetFloat("SEVol", volume);
    }
    //  �V���b�^�[������
    public void StartSyutterDown(float time)
    {
        m_audioSource.PlayOneShot(m_downClipAudio);

        m_backImage.SetActive(true);
        m_pauseTitle.SetActive(false);
        //  ������
        m_fadeFinish = false;

        m_backImage.transform.localPosition = new Vector3(0.0f, 1080.0f, 0.0f);

        var doT = DOTween.Sequence()
                .Append(m_backImage.transform.DOLocalMoveY(0.0f, time))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  �V���b�^�[�オ��
    public void StartSyutterOn(float time)
    {
        m_audioSource.PlayOneShot(m_downClipAudio);

        //  ������
        m_fadeFinish = false;
        m_backImage.SetActive(true);
        m_pauseTitle.SetActive(false);

        m_backImage.transform.localPosition = new Vector3(0.0f, 0.0f, 0.0f);

        var doT = DOTween.Sequence()
                .Append(m_backImage.transform.DOLocalMoveY(1080.0f, time))
                .AppendCallback(() => m_backImage.SetActive(false))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  �t�F�C�h�C���J�n
    public void StartFadeIn(float time)
    {
        //  ������
        m_fadeFinish = false;

        //  �摜�̓����x���P�ɂ���
        m_fadeImage.color = new Color(0f, 0f, 0f, 1f);
        m_fadeImage.gameObject.SetActive(true);

        var doT = DOTween.Sequence()
                .Append(m_fadeImage.DOFade(0f, time))
                .AppendCallback(() => m_fadeImage.gameObject.SetActive(false))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  �t�F�C�h�A�E�g�J�n
    public void StartFadeOut(float time)
    {
        //  ������
        m_fadeFinish = false;

        //  �摜�̓����x���P�ɂ���
        m_fadeImage.color = new Color(0f, 0f, 0f, 0f);
        m_fadeImage.gameObject.SetActive(true);

        var doT = DOTween.Sequence()
                .Append(m_fadeImage.DOFade(1f, time))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  �t�F�C�h�̏I����n��
    public bool GetFadeFinish()
    {
        return m_fadeFinish;
    }

    private void ExitOption()
    {
        m_inputWait = true;
        //  �I�v�V���������
        m_isOption = false;
        //  �I����������
        m_optionSelect = OptionSelect.Null;
        //  �m�F��ʔ�\��
        m_confirmation.SetActive(false);
        //  �F��߂�
        Color color = m_selectImages[(int)OptionSelect.StageSelect].color;
        color.a = 1.0f;
        m_selectImages[(int)OptionSelect.StageSelect].color = color;

        var doT = DOTween.Sequence()
                .Append(m_backImage.transform.DOLocalMoveY(1080.0f, 0.3f).SetEase(Ease.Linear))
                .AppendCallback(() => m_fadeFinish = true)
                .AppendCallback(() => m_inputWait = false);
    }

    public bool GetInputWait()
    {
        return m_inputWait;
    }
}
