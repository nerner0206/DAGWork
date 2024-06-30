using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using System.IO;

//  プレイシーンの状態
public enum PlaySceneState
{
    Before,
    CountDown,
    Playing,
    Finish
}

//  ウェーブのクラス
[System.Serializable]
public class Wave
{
    public EnemyKind[] enemis;
}

//  プレイ内の状態
public enum PlayingState
{
    EnemyCreate,
    Battle,
    AllDead
}


public class PlayManager : MonoBehaviour
{
    //  プレイシーンの状態
    private PlaySceneState playSceneState;
    //  プレイ内の状態
    private PlayingState playingState;

    //  プレイヤーオブジェクト
    [SerializeField] private GameObject player;
    //  プレイヤーの制御スクリプト
    private PlayerController playerController;
    //  武器の親オブジェクト(右手)
    [SerializeField] private GameObject haveWeapon;

    [SerializeField] private GameObject handle;
    [SerializeField] private List<GameObject> shapePrefabs;

    //  メインカメラ
    [SerializeField] private GameObject vCam;

    //  重さ
    private float mass;

    //  スコア
    private int score;
    public static int highScore = 0;

    //  敵のプレハブ
    [SerializeField] private List<GameObject> enemyPrefab;
    //  作成した敵を格納する
    private List<GameObject> enemies;

    //  ウェーブ
    [SerializeField] private Wave[] waveValues;
    private int waveNum;

    //  画面を止める時間
    private float pauseTime;
    //  画面を揺らすタイミング
    private bool Shaking;

    //  フェイド
    [SerializeField] Fade fade;
    //  フェイドタイム
    [SerializeField] private float fadeTime = 0.0f;
    //  フェイド終了を判定
    private bool fadeFinish;
    private bool fadeStart;

    //  UI
    //  今のウェーブ
    [SerializeField] private Text nowWave;
    //  最大ウェーブ
    [SerializeField] private Text maxWave;

    //  ハイスコア
    [SerializeField] private Text highScoreT;
    //  スコア
    [SerializeField] private Text scoreT;

    //  終了パネル
    [SerializeField] private GameObject finishPanel;
    //  最後のスコア
    [SerializeField] private Text finishScore;

    [SerializeField] private GameObject createP;
    //  ゲームパッド
    private Gamepad gamepad;

    void Start()
    {
        //  カメラの初期化
        vCam.GetComponent<PlayCamera>().Init();

        //  初期化
        playSceneState = PlaySceneState.Before;
        playingState = PlayingState.EnemyCreate;

        //  第一ウェーブ
        waveNum = 0;

        //  プレイヤー制御のスクリプトを取得
        playerController = player.GetComponent<PlayerController>();
        //  プレイヤーの初期化
        playerController.PlayerInit();

        //  エフェクトを出す
        Instantiate(createP, player.gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f), Quaternion.Euler(new Vector3(-90.0f, 0.0f, 0.0f)));

        // 念のためファイルの存在チェック
        if (!File.Exists(Initialize.dataPathes[SelectManager.weaponDataNumber])) return;
        // JSONデータとしてデータを読み込む
        var json = File.ReadAllText(Initialize.dataPathes[SelectManager.weaponDataNumber]);
        Debug.Log(json);
        // JSON形式からオブジェクトにデシリアライズ
        var obj = JsonUtility.FromJson<Weapon>(json);
        Debug.Log(obj);

        //  ハンドル生成
        GameObject weapon = Instantiate(handle);
        for (int i = 0; i < obj.ID.Length; i++)
        {
            //  生成
            GameObject part = Instantiate(shapePrefabs[obj.ID[i]], obj.pos[i], Quaternion.Euler(obj.rot[i]));
            //  親設定
            part.transform.parent = weapon.transform;
            //  サイズ調整
            part.transform.localScale = obj.sca[i];
        }
        
        //  武器を子オブジェクトへ
        weapon.transform.parent = haveWeapon.transform;
        //  武器の位置・角度調整
        weapon.transform.localPosition = new Vector3(-0.844f, 0.145f, -0.402f);
        weapon.transform.localEulerAngles = new Vector3(0.436f, -30.855f, 89.739f);
        //  プレイヤーに武器オブジェクトをセット
        playerController.SetWeaponObject(weapon);

        //  質量を受け取る
        mass = MakeManager.mass;
        //mass = 0.0f;

        //  重さの割合を取る
        float massRatio = mass / MakeManager.MAX_MASS;
        //  比率からアニメーション速度を設定
        playerController.SetAnimSpeed(massRatio);
        //  比率から攻撃力を設定
        playerController.SetAttackPower(massRatio);

        //  敵リストを初期化
        enemies = new List<GameObject>();

        pauseTime = 0.0f;

        Shaking = false;

        //  ウェーブを変更
        nowWave.text = (waveNum + 1).ToString();
        //  最大ウェーブを入れる
        maxWave.text = waveValues.Length.ToString();

        //  スコアの初期化
        score = 0;
        //  スコアの更新
        scoreT.text = score.ToString("00000");
        //  ハイスコアの更新
        highScoreT.text = highScore.ToString("00000");

        //  パネルを消す
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
                //  更新処理
                gamepad = Gamepad.current;
                if (gamepad == null) return;

                //  状態遷移の条件
                if (true)
                {
                    //  状態をカウントダウンへ
                    playSceneState = PlaySceneState.CountDown;
                }
                break;
            case PlaySceneState.CountDown:
                //  更新処理

                //  状態遷移の条件
                if (true)
                {
                    //  状態をプレイングへ
                    playSceneState = PlaySceneState.Playing;
                }
                break;
            case PlaySceneState.Playing:
                //  カメラの更新処理
                vCam.GetComponent<PlayCamera>().CamUpdate();
                //  更新処理
                PlayingUpdata();

                //  プレイヤーが死んだら
                if(playerController.GetPlayerState() == PlayerState.Dead)
                {
                    //  状態を終了へ
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
        //  パネルの表示
        finishPanel.SetActive(true);
        //  スコアを入れる
        finishScore.text = score.ToString("00000");
        //  止める
        Time.timeScale = 0.0f;
    }

    public void PushBackButton()
    {
        //  動かす
        Time.timeScale = 1.0f;
        //  画面変更
        fade.FadeIn(fadeTime, () => SceneManager.LoadScene("TitleScene"));
    }

    //  プレイング状態の更新処理
    private void PlayingUpdata()
    {
        //  画面揺れを止める
        Shaking = false;

        //  プレイヤー制御の更新処理
        playerController.PlayerUpdate();

        switch(playingState)
        {
            case PlayingState.EnemyCreate:
                //  ウェーブ番号の敵を全て生成
                foreach(var enemy in waveValues[waveNum].enemis)
                {
                    //  敵の種類をキャストして生成
                    GameObject ene = Instantiate(enemyPrefab[(int)enemy]);
                    //  生成位置
                    ene.transform.position = new Vector3(UnityEngine.Random.Range(-15.0f, 15.0f), 8.0f, UnityEngine.Random.Range(-15.0f, 15.0f));
                    //  初期化
                    ene.GetComponent<EnemyController>().EnemyInit(player);
                    //  リストに追加
                    enemies.Add(ene);

                    //  エフェクトを出す
                    Instantiate(createP, ene.gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f), Quaternion.Euler(new Vector3(-90.0f, 0.0f, 0.0f)));
                }

                //  バトルへ
                playingState = PlayingState.Battle;

                break;
            case PlayingState.Battle:
                //  全ての敵が死んでいるとする
                bool allDead = true;

                //  作成した数の敵の更新処理
                foreach (var enemy in enemies)
                {
                    //  更新処理
                    enemy.GetComponent<EnemyController>().EnemyUpdate();

                    //  完全な死亡状態になっている
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

                    //  完全な死亡状態になっている
                    if (enemy.GetComponent<EnemyController>().GetEnemyState() == EnemyState.Dead) continue;

                    //  一体でも生存しているならfalseへ
                    allDead = false;
                }

                //  trueなら全員死んでいる
                if(allDead) playingState = PlayingState.AllDead;

                break;
            case PlayingState.AllDead:
                //  作成した数の敵を削除
                foreach (var enemy in enemies)
                {
                    //  削除
                    Destroy(enemy);
                }
                //  リセット
                enemies.Clear();
                //  初期化
                enemies = new List<GameObject>();

                //  次のウェーブへ
                waveNum++;
                //  ウェーブを変更
                nowWave.text = (waveNum + 1).ToString();

                //  次のウェーブがない場合はゲームを終了
                if (waveValues.Length <= waveNum)
                {
                    playSceneState = PlaySceneState.Finish;
                    FinishInit();
                }
                //  次のウェーブがある場合は敵を生成
                else playingState = PlayingState.EnemyCreate;

                break;
        }
    }
}