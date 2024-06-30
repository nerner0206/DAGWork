using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;

public class TitleManager : MonoBehaviour
{
    //  ����v���n�u
    [SerializeField] private List<GameObject> weaponPrefabs = new List<GameObject>();

    //  ��������
    [SerializeField] private float CREATE_TIME = 0.0f;
    //  �����J�E���^
    private float createCount;

    //  �t�F�C�h���x
    [SerializeField] private float fadeTime = 0.0f;

    //  UI���i�[����I�u�W�F�N�g

    //  �ݒ�L�����o�X
    [SerializeField] private GameObject configCanvas;

    //  �J�n�{�^��
    [SerializeField] private GameObject startButton;
    //  �`���[�g���A���{�^��
    [SerializeField] private GameObject tutorialButton;
    //  �v���C�{�^��
    [SerializeField] private GameObject playButton;

    //  ������
    [SerializeField] private GameObject ruluBook;
    [SerializeField] private GameObject ruluPage01;
    [SerializeField] private GameObject ruluPage02;
    [SerializeField] private GameObject ruluLeft;
    [SerializeField] private GameObject ruluRight;

    //  �t�F�C�h�J�ڗp
    [SerializeField] Fade fade;
    //  �t�F�C�h�̏I��
    private bool fadeFinish;
    private bool fadeStart;

    //  �n�C�X�R�A
    public static int highScore = 0;

    //  �h���I�u�W�F�N�g
    [SerializeField] private GameObject shakeUI;

    Gamepad gamepad;

    private void Awake()
    {
        //  �ݒ�{�^�����V�[���Ԃŋ��L����
        DontDestroyOnLoad(configCanvas);
    }

    //  ������
    private void Start()
    {
        //  �������Ԃ�������
        createCount = 0.0f;

        //  �J�n�{�^��
        startButton.SetActive(true);
        //  �`���[�g���A���{�^��
        tutorialButton.SetActive(false);
        //  �v���C�{�^��
        playButton.SetActive(false);

        //  �t�F�C�h�I���𔻒�
        fadeFinish = false;
        fadeStart = true;
        //  �t�F�C�h���I��
        
    }

    private void FadeFinish()
    {
        fadeFinish = true;
    }

    //  �X�V����
    private void Update()
    {
        if (fadeStart)
        {
            fade.FadeOut(fadeTime, () => FadeFinish());
            fadeStart = false;
        }
        if (!fadeFinish) return;

        //  ����𐶐�
        WeaponCreate();

        gamepad = Gamepad.current;
        if (gamepad == null) return;

        if(gamepad.bButton.wasPressedThisFrame)
        {
            PushPlayButton();

            ////  �J�n�{�^�����\��
            //startButton.SetActive(false);
            ////  �`���[�g���A���{�^����\��
            //tutorialButton.SetActive(true);
            ////  �v���C�{�^����\��
            //playButton.SetActive(true);
        }
    }

    private void WeaponCreate()
    {
        //  �������Ԃ𑝂₷
        createCount += Time.deltaTime;

        //  ������Ԃ�
        if (createCount < CREATE_TIME) return;

        //  �������Ԃ����Z�b�g
        createCount = 0.0f;

        shakeUI.GetComponent<ShakeByPerlinNoise>().StartShake(0.5f, 10.0f, 10.0f);

        //  �������镐��̔ԍ�
        int weaponNumber = Random.Range(0, weaponPrefabs.Count);
        //  ����𐶐�����
        GameObject weapon = Instantiate(weaponPrefabs[weaponNumber]);
    }

    //  �Q�[�����n�߂�
    public void PushStartButton()
    {
        //  �J�n�{�^�����\��
        startButton.SetActive(false);
        //  �`���[�g���A���{�^����\��
        tutorialButton.SetActive(true);
        //  �v���C�{�^����\��
        playButton.SetActive(true);

        SoundManager.instance.ButtonSE();
    }
    
    //  �Q�[�����n�߂�
    public void PushPlayButton()
    {
        //  ���C�N�V�[���ֈړ�
        fade.FadeIn(fadeTime, () => SceneManager.LoadScene("SelectScene"));

        SoundManager.instance.ButtonSE();
    }

    //  �`���[�g���A�����n�߂�
    public void PushTutorialButton()
    {
        //  ���[���u�b�N��\��
        ruluBook.SetActive(true);

        ruluPage01.SetActive(true);
        ruluPage02.SetActive(false);

        ruluRight.SetActive(true);
        ruluLeft.SetActive(false);

        SoundManager.instance.ButtonSE();
    }
    //  �E�y�[�W
    public void PushRightPage()
    {
        ruluPage01.SetActive(false);
        ruluPage02.SetActive(true);

        ruluRight.SetActive(false);
        ruluLeft.SetActive(true);

        SoundManager.instance.ButtonSE();
    }
    //  ���y�[�W
    public void PushLeftPage()
    {
        ruluPage01.SetActive(true);
        ruluPage02.SetActive(false);

        ruluRight.SetActive(true);
        ruluLeft.SetActive(false);

        SoundManager.instance.ButtonSE();
    }

    public void Batu()
    {
        ruluBook.SetActive(false);

        SoundManager.instance.ButtonSE();
    }
}
