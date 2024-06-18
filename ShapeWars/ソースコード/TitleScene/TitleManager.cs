using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;

public class TitleManager : MonoBehaviour
{
    //  武器プレハブ
    [SerializeField] private List<GameObject> weaponPrefabs = new List<GameObject>();

    //  生成時間
    [SerializeField] private float CREATE_TIME = 0.0f;
    //  生成カウンタ
    private float createCount;

    //  フェイド速度
    [SerializeField] private float fadeTime = 0.0f;

    //  UIを格納するオブジェクト

    //  設定キャンバス
    [SerializeField] private GameObject configCanvas;

    //  開始ボタン
    [SerializeField] private GameObject startButton;
    //  チュートリアルボタン
    [SerializeField] private GameObject tutorialButton;
    //  プレイボタン
    [SerializeField] private GameObject playButton;

    //  説明書
    [SerializeField] private GameObject ruluBook;
    [SerializeField] private GameObject ruluPage01;
    [SerializeField] private GameObject ruluPage02;
    [SerializeField] private GameObject ruluLeft;
    [SerializeField] private GameObject ruluRight;

    //  フェイド遷移用
    [SerializeField] Fade fade;
    //  フェイドの終了
    private bool fadeFinish;
    private bool fadeStart;

    //  ハイスコア
    public static int highScore = 0;

    //  揺れるオブジェクト
    [SerializeField] private GameObject shakeUI;

    Gamepad gamepad;

    private void Awake()
    {
        //  設定ボタンをシーン間で共有する
        DontDestroyOnLoad(configCanvas);
    }

    //  初期化
    private void Start()
    {
        //  生成時間を初期化
        createCount = 0.0f;

        //  開始ボタン
        startButton.SetActive(true);
        //  チュートリアルボタン
        tutorialButton.SetActive(false);
        //  プレイボタン
        playButton.SetActive(false);

        //  フェイド終了を判定
        fadeFinish = false;
        fadeStart = true;
        //  フェイドを終了
        
    }

    private void FadeFinish()
    {
        fadeFinish = true;
    }

    //  更新処理
    private void Update()
    {
        if (fadeStart)
        {
            fade.FadeOut(fadeTime, () => FadeFinish());
            fadeStart = false;
        }
        if (!fadeFinish) return;

        //  武器を生成
        WeaponCreate();

        gamepad = Gamepad.current;
        if (gamepad == null) return;

        if(gamepad.bButton.wasPressedThisFrame)
        {
            PushPlayButton();

            ////  開始ボタンを非表示
            //startButton.SetActive(false);
            ////  チュートリアルボタンを表示
            //tutorialButton.SetActive(true);
            ////  プレイボタンを表示
            //playButton.SetActive(true);
        }
    }

    private void WeaponCreate()
    {
        //  生成時間を増やす
        createCount += Time.deltaTime;

        //  処理を返す
        if (createCount < CREATE_TIME) return;

        //  生成時間をリセット
        createCount = 0.0f;

        shakeUI.GetComponent<ShakeByPerlinNoise>().StartShake(0.5f, 10.0f, 10.0f);

        //  生成する武器の番号
        int weaponNumber = Random.Range(0, weaponPrefabs.Count);
        //  武器を生成する
        GameObject weapon = Instantiate(weaponPrefabs[weaponNumber]);
    }

    //  ゲームを始める
    public void PushStartButton()
    {
        //  開始ボタンを非表示
        startButton.SetActive(false);
        //  チュートリアルボタンを表示
        tutorialButton.SetActive(true);
        //  プレイボタンを表示
        playButton.SetActive(true);

        SoundManager.instance.ButtonSE();
    }
    
    //  ゲームを始める
    public void PushPlayButton()
    {
        //  メイクシーンへ移動
        fade.FadeIn(fadeTime, () => SceneManager.LoadScene("SelectScene"));

        SoundManager.instance.ButtonSE();
    }

    //  チュートリアルを始める
    public void PushTutorialButton()
    {
        //  ルールブックを表示
        ruluBook.SetActive(true);

        ruluPage01.SetActive(true);
        ruluPage02.SetActive(false);

        ruluRight.SetActive(true);
        ruluLeft.SetActive(false);

        SoundManager.instance.ButtonSE();
    }
    //  右ページ
    public void PushRightPage()
    {
        ruluPage01.SetActive(false);
        ruluPage02.SetActive(true);

        ruluRight.SetActive(false);
        ruluLeft.SetActive(true);

        SoundManager.instance.ButtonSE();
    }
    //  左ページ
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
