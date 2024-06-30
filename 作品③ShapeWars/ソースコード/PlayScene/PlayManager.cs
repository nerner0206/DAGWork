using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using System.IO;

//  �v���C�V�[���̏��
public enum PlaySceneState
{
    Before,
    CountDown,
    Playing,
    Finish
}

//  �E�F�[�u�̃N���X
[System.Serializable]
public class Wave
{
    public EnemyKind[] enemis;
}

//  �v���C���̏��
public enum PlayingState
{
    EnemyCreate,
    Battle,
    AllDead
}


public class PlayManager : MonoBehaviour
{
    //  �v���C�V�[���̏��
    private PlaySceneState playSceneState;
    //  �v���C���̏��
    private PlayingState playingState;

    //  �v���C���[�I�u�W�F�N�g
    [SerializeField] private GameObject player;
    //  �v���C���[�̐���X�N���v�g
    private PlayerController playerController;
    //  ����̐e�I�u�W�F�N�g(�E��)
    [SerializeField] private GameObject haveWeapon;

    [SerializeField] private GameObject handle;
    [SerializeField] private List<GameObject> shapePrefabs;

    //  ���C���J����
    [SerializeField] private GameObject vCam;

    //  �d��
    private float mass;

    //  �X�R�A
    private int score;
    public static int highScore = 0;

    //  �G�̃v���n�u
    [SerializeField] private List<GameObject> enemyPrefab;
    //  �쐬�����G���i�[����
    private List<GameObject> enemies;

    //  �E�F�[�u
    [SerializeField] private Wave[] waveValues;
    private int waveNum;

    //  ��ʂ��~�߂鎞��
    private float pauseTime;
    //  ��ʂ�h�炷�^�C�~���O
    private bool Shaking;

    //  �t�F�C�h
    [SerializeField] Fade fade;
    //  �t�F�C�h�^�C��
    [SerializeField] private float fadeTime = 0.0f;
    //  �t�F�C�h�I���𔻒�
    private bool fadeFinish;
    private bool fadeStart;

    //  UI
    //  ���̃E�F�[�u
    [SerializeField] private Text nowWave;
    //  �ő�E�F�[�u
    [SerializeField] private Text maxWave;

    //  �n�C�X�R�A
    [SerializeField] private Text highScoreT;
    //  �X�R�A
    [SerializeField] private Text scoreT;

    //  �I���p�l��
    [SerializeField] private GameObject finishPanel;
    //  �Ō�̃X�R�A
    [SerializeField] private Text finishScore;

    [SerializeField] private GameObject createP;
    //  �Q�[���p�b�h
    private Gamepad gamepad;

    void Start()
    {
        //  �J�����̏�����
        vCam.GetComponent<PlayCamera>().Init();

        //  ������
        playSceneState = PlaySceneState.Before;
        playingState = PlayingState.EnemyCreate;

        //  ���E�F�[�u
        waveNum = 0;

        //  �v���C���[����̃X�N���v�g���擾
        playerController = player.GetComponent<PlayerController>();
        //  �v���C���[�̏�����
        playerController.PlayerInit();

        //  �G�t�F�N�g���o��
        Instantiate(createP, player.gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f), Quaternion.Euler(new Vector3(-90.0f, 0.0f, 0.0f)));

        // �O�̂��߃t�@�C���̑��݃`�F�b�N
        if (!File.Exists(Initialize.dataPathes[SelectManager.weaponDataNumber])) return;
        // JSON�f�[�^�Ƃ��ăf�[�^��ǂݍ���
        var json = File.ReadAllText(Initialize.dataPathes[SelectManager.weaponDataNumber]);
        Debug.Log(json);
        // JSON�`������I�u�W�F�N�g�Ƀf�V���A���C�Y
        var obj = JsonUtility.FromJson<Weapon>(json);
        Debug.Log(obj);

        //  �n���h������
        GameObject weapon = Instantiate(handle);
        for (int i = 0; i < obj.ID.Length; i++)
        {
            //  ����
            GameObject part = Instantiate(shapePrefabs[obj.ID[i]], obj.pos[i], Quaternion.Euler(obj.rot[i]));
            //  �e�ݒ�
            part.transform.parent = weapon.transform;
            //  �T�C�Y����
            part.transform.localScale = obj.sca[i];
        }
        
        //  ������q�I�u�W�F�N�g��
        weapon.transform.parent = haveWeapon.transform;
        //  ����̈ʒu�E�p�x����
        weapon.transform.localPosition = new Vector3(-0.844f, 0.145f, -0.402f);
        weapon.transform.localEulerAngles = new Vector3(0.436f, -30.855f, 89.739f);
        //  �v���C���[�ɕ���I�u�W�F�N�g���Z�b�g
        playerController.SetWeaponObject(weapon);

        //  ���ʂ��󂯎��
        mass = MakeManager.mass;
        //mass = 0.0f;

        //  �d���̊��������
        float massRatio = mass / MakeManager.MAX_MASS;
        //  �䗦����A�j���[�V�������x��ݒ�
        playerController.SetAnimSpeed(massRatio);
        //  �䗦����U���͂�ݒ�
        playerController.SetAttackPower(massRatio);

        //  �G���X�g��������
        enemies = new List<GameObject>();

        pauseTime = 0.0f;

        Shaking = false;

        //  �E�F�[�u��ύX
        nowWave.text = (waveNum + 1).ToString();
        //  �ő�E�F�[�u������
        maxWave.text = waveValues.Length.ToString();

        //  �X�R�A�̏�����
        score = 0;
        //  �X�R�A�̍X�V
        scoreT.text = score.ToString("00000");
        //  �n�C�X�R�A�̍X�V
        highScoreT.text = highScore.ToString("00000");

        //  �p�l��������
        finishPanel.SetActive(false);

        fadeFinish = false;
        fadeStart = true;
    }

    private void FadeFinish()
    {
        fadeFinish = true;
    }

    // Update is called once per frame
    void Update()
    {
        if (fadeStart)
        {
            fade.FadeOut(fadeTime, () => FadeFinish());
            fadeStart = false;
        }
        if (!fadeFinish) return;
        
        if(highScore < score)
        {
            highScore = score;
            highScoreT.text = highScore.ToString("00000");
        }

        switch (playSceneState)
        {
            case PlaySceneState.Before:
                //  �X�V����
                gamepad = Gamepad.current;
                if (gamepad == null) return;

                //  ��ԑJ�ڂ̏���
                if (true)
                {
                    //  ��Ԃ��J�E���g�_�E����
                    playSceneState = PlaySceneState.CountDown;
                }
                break;
            case PlaySceneState.CountDown:
                //  �X�V����

                //  ��ԑJ�ڂ̏���
                if (true)
                {
                    //  ��Ԃ��v���C���O��
                    playSceneState = PlaySceneState.Playing;
                }
                break;
            case PlaySceneState.Playing:
                //  �J�����̍X�V����
                vCam.GetComponent<PlayCamera>().CamUpdate();
                //  �X�V����
                PlayingUpdata();

                //  �v���C���[�����񂾂�
                if(playerController.GetPlayerState() == PlayerState.Dead)
                {
                    //  ��Ԃ��I����
                    playSceneState = PlaySceneState.Finish;
                    FinishInit();
                }
                break;
            case PlaySceneState.Finish:


                break;
        }
    }

    private void FinishInit()
    {
        //  �p�l���̕\��
        finishPanel.SetActive(true);
        //  �X�R�A������
        finishScore.text = score.ToString("00000");
        //  �~�߂�
        Time.timeScale = 0.0f;
    }

    public void PushBackButton()
    {
        //  ������
        Time.timeScale = 1.0f;
        //  ��ʕύX
        fade.FadeIn(fadeTime, () => SceneManager.LoadScene("TitleScene"));
    }

    //  �v���C���O��Ԃ̍X�V����
    private void PlayingUpdata()
    {
        //  ��ʗh����~�߂�
        Shaking = false;

        //  �v���C���[����̍X�V����
        playerController.PlayerUpdate();

        switch(playingState)
        {
            case PlayingState.EnemyCreate:
                //  �E�F�[�u�ԍ��̓G��S�Đ���
                foreach(var enemy in waveValues[waveNum].enemis)
                {
                    //  �G�̎�ނ��L���X�g���Đ���
                    GameObject ene = Instantiate(enemyPrefab[(int)enemy]);
                    //  �����ʒu
                    ene.transform.position = new Vector3(UnityEngine.Random.Range(-15.0f, 15.0f), 8.0f, UnityEngine.Random.Range(-15.0f, 15.0f));
                    //  ������
                    ene.GetComponent<EnemyController>().EnemyInit(player);
                    //  ���X�g�ɒǉ�
                    enemies.Add(ene);

                    //  �G�t�F�N�g���o��
                    Instantiate(createP, ene.gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f), Quaternion.Euler(new Vector3(-90.0f, 0.0f, 0.0f)));
                }

                //  �o�g����
                playingState = PlayingState.Battle;

                break;
            case PlayingState.Battle:
                //  �S�Ă̓G������ł���Ƃ���
                bool allDead = true;

                //  �쐬�������̓G�̍X�V����
                foreach (var enemy in enemies)
                {
                    //  �X�V����
                    enemy.GetComponent<EnemyController>().EnemyUpdate();

                    //  ���S�Ȏ��S��ԂɂȂ��Ă���
                    if (enemy.GetComponent<EnemyController>().IsDead)
                    {
                        enemy.GetComponent<EnemyController>().IsDead = false;

                        switch (enemy.GetComponent<EnemyController>().GetEnemyKind())
                        {
                            case EnemyKind.Enemy01:
                                score += 100;
                                scoreT.text = score.ToString("00000");
                                break;
                            case EnemyKind.Enemy02:
                                score += 300;
                                scoreT.text = score.ToString("00000");
                                break;
                            case EnemyKind.Enemy03:
                                score += 500;
                                scoreT.text = score.ToString("00000");
                                break;
                            case EnemyKind.Enemy04:
                                score += 1000;
                                scoreT.text = score.ToString("00000");
                                break;
                        }
                    }

                    //  ���S�Ȏ��S��ԂɂȂ��Ă���
                    if (enemy.GetComponent<EnemyController>().GetEnemyState() == EnemyState.Dead) continue;

                    //  ��̂ł��������Ă���Ȃ�false��
                    allDead = false;
                }

                //  true�Ȃ�S������ł���
                if(allDead) playingState = PlayingState.AllDead;

                break;
            case PlayingState.AllDead:
                //  �쐬�������̓G���폜
                foreach (var enemy in enemies)
                {
                    //  �폜
                    Destroy(enemy);
                }
                //  ���Z�b�g
                enemies.Clear();
                //  ������
                enemies = new List<GameObject>();

                //  ���̃E�F�[�u��
                waveNum++;
                //  �E�F�[�u��ύX
                nowWave.text = (waveNum + 1).ToString();

                //  ���̃E�F�[�u���Ȃ��ꍇ�̓Q�[�����I��
                if (waveValues.Length <= waveNum)
                {
                    playSceneState = PlaySceneState.Finish;
                    FinishInit();
                }
                //  ���̃E�F�[�u������ꍇ�͓G�𐶐�
                else playingState = PlayingState.EnemyCreate;

                break;
        }
    }
}