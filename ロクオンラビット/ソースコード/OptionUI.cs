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
    //  このオブジェクトを格納する
    private static GameObject m_instance;
    //  このオブジェクトを渡す
    public static GameObject GetInstance { get { return m_instance; } }

    //  Option中
    public static bool m_isOption = false;

    [SerializeField, Tooltip("AudioMixer")]
    private AudioMixer m_audioMixer;

    [SerializeField, Tooltip("背景プレハブ")]
    private GameObject m_backImagePrefab;

    [SerializeField, Tooltip("スティックのデッドゾーン")]
    private float m_deadZone = 0.1f;

    [SerializeField, Tooltip("入力のクールタイム")]
    private float m_coolTime = 0.5f;

    [SerializeField, Tooltip("確認画面プレハブ")] 
    private GameObject m_confirmationPrefab;

    [SerializeField, Tooltip("番号")]
    private Sprite[] m_numImages;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;
    [SerializeField, Tooltip("カーソル移動音")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("決定音")]
    private AudioClip m_decideAudio;
    [SerializeField, Tooltip("シャッター閉じる音")]
    private AudioClip m_downClipAudio;

    //  入力
    private PlayerControll m_inputActions;
    //  現在のシーン
    private AllScene m_nowScene;

    //  シーンのマネージャーを取得する
    private SceneManagement m_sceneManager;
    
    //  背景オブジェクト
    private GameObject m_backImage;
    //  ポーズタイトルオブジェクト
    private GameObject m_pauseTitle;
    //  選択オブジェクト
    private GameObject[] m_selectObjs;
    //  選択画像
    private Image[] m_selectImages;
    //  アイコンオブジェクト
    private GameObject m_selectIcon;
    //  アイコン座標
    private Vector3[] m_iconPoses;
    //  選択アイコン画像
    private Image m_selectIconImage;
    //  選択番号
    private int m_selectNum;
    
    //  タイマー
    private float m_timer;

    //  確認画面オブジェクト
    private GameObject m_confirmation;
    //  Yes/Noオブジェクト
    private GameObject[] m_YNSelectObjs;
    //  Yes/No選択番号
    private int m_YNnum;

    //  オプションの選択クラス
    private OptionSelect m_optionSelect;

    //  半径
    private float m_radian;

    //  BGMの音量
    private int m_bgmVol;
    //  SEの音量
    private int m_seVol;
    //  BGMの音量画像
    private Image m_bgmVolImage;
    //  SEの音量画像
    private Image m_seVolImage;

    //  入力タイマー
    private float m_inputTimer;
    //  入力待機
    private bool m_inputWait;

    /// <summary>
    /// フェイドイン/アウト用
    /// </summary>
    [SerializeField, Tooltip("フェイド用パネル")] 
    private GameObject m_panelPrefab;

    //  フェイド画像
    private Image m_fadeImage;
    //  フェイド終了
    private bool m_fadeFinish;

    public void Init()
    {
        //  取得
        if (m_instance == null)
        {
            DontDestroyOnLoad(gameObject);
            m_instance = gameObject;
        }
        else
        {
            Destroy(gameObject);
        }

        ////  Canvasの初期設定  //////////////////////////////////////////////////////////////////////////////////////////////////////

        //  canvasの設定
        gameObject.GetComponent<Canvas>().renderMode = RenderMode.ScreenSpaceOverlay;
        gameObject.GetComponent<Canvas>().sortingOrder = 1000;
        //  CanvasScalerの設定
        gameObject.GetComponent<CanvasScaler>().uiScaleMode = CanvasScaler.ScaleMode.ScaleWithScreenSize;
        gameObject.GetComponent<CanvasScaler>().referenceResolution = new Vector2(1920, 1080);

        GameObject man = GameObject.FindGameObjectWithTag("Manager");
        m_sceneManager = man.GetComponent<SceneManagement>();

        m_optionSelect = OptionSelect.Null;

        ////  UIを生成  ////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

        //  初期画面
        //  子オブジェクトを生成
        m_backImage = Instantiate(m_backImagePrefab, gameObject.transform);
        //  位置を上に
        m_backImage.transform.localPosition = new Vector3(0.0f, 1080.0f, 0.0f);
        //  非表示
        m_backImage.SetActive(false);
        m_pauseTitle = m_backImage.transform.GetChild(0).gameObject;
        //  子オブジェクトの数
        int n = m_pauseTitle.transform.childCount;
        //  初期化
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
        //  アイコンを取得
        m_selectIcon = m_pauseTitle.transform.GetChild(n - 1).gameObject;
        //  アイコンの色を取得
        m_selectIconImage = m_selectIcon.GetComponent<Image>();

        m_selectNum = 0;

        m_selectIcon.transform.localPosition = m_iconPoses[m_selectNum];

        //  確認画面
        //  子オブジェクトを生成
        m_confirmation = m_pauseTitle.transform.GetChild(n - 2).gameObject;
        //  非表示
        m_confirmation.SetActive(false);

        //  オブジェクトを取得
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

        //  生成
        GameObject fade = Instantiate(m_panelPrefab, gameObject.transform);
        //  Image取得
        m_fadeImage = fade.GetComponent<Image>();
        //  非表示
        fade.SetActive(true);
    }
    // Update is called once per frame
    private void Update()
    {
        if (m_sceneManager == null) return;
        //  オプションを開けない状態
        if (m_sceneManager.NonOptionState()) return;
        //  入力を受け取る(タイトルシーンは例外)
        if (m_inputActions.Option.Option.WasPressedThisFrame() && m_nowScene != AllScene.TitleScene)
        {
            //  まだオプションを開いていない
            if(!m_isOption)
            {
                OpenOption();
            }
            //  既にオプションを開いている
            else
            {
                ExitOption();
            }
            return;
        }

        //  オプションを開いていなければ処理しない
        if (!m_isOption) return;

        switch(m_optionSelect)
        {
            case OptionSelect.BGM:
                //  スライダーを動かす
                SliderMove(ref m_bgmVol, ref m_bgmVolImage);
                SetAudioMixerBGM((float)m_bgmVol / 9.0f);
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  色を戻す
                    BackColor();

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.SE:
                //  スライダーを動かす
                SliderMove(ref m_seVol, ref m_seVolImage);
                SetAudioMixerSE((m_seVol) / 9.0f);
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  色を戻す
                    BackColor();

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.StageSelect:
                //  更新
                YNSelect();
                //  決定
                if(m_inputActions.Option.Decide.WasPressedThisFrame())
                {
                    m_audioSource.PlayOneShot(m_decideAudio);
                    //  ×
                    if (m_YNnum == 0)
                    {
                        //  色を戻す
                        BackColor();
                        //  確認画面を非表示
                        m_confirmation.SetActive(false);

                        m_optionSelect = OptionSelect.Null;
                    }
                    //  〇
                    else
                    {
                        //  オプションを閉じる
                        CloseOption();
                        //  シャッターを下まで締め切る
                        //  シーン遷移
                        var doT = DOTween.Sequence()
                            .Append(m_backImage.transform.DOLocalMoveY(0.0f, 0.2f))
                            .AppendCallback(() => SceneManager.LoadScene("SelectStage"));
                    }
                }
                
                //  戻る
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  色を戻す
                    BackColor();
                    //  確認画面を非表示
                    m_confirmation.SetActive(false);

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.End:
                //  更新
                YNSelect();
                //  決定
                if (m_inputActions.Option.Decide.WasPressedThisFrame())
                {
                    m_audioSource.PlayOneShot(m_decideAudio);
                    //  ×
                    if (m_YNnum == 0)
                    {
                        //  色を戻す
                        BackColor();
                        //  確認画面を非表示
                        m_confirmation.SetActive(false);

                        m_optionSelect = OptionSelect.Null;
                    }
                    //  〇
                    else
                    {
#if UNITY_EDITOR
                        UnityEditor.EditorApplication.isPlaying = false;//ゲームプレイ終了
#else
    Application.Quit();//ゲームプレイ終了
#endif
                    }
                }
                //  戻る
                if (m_inputActions.Option.Back.WasPressedThisFrame())
                {
                    //  色を戻す
                    BackColor();
                    //  確認画面を非表示
                    m_confirmation.SetActive(false);

                    m_optionSelect = OptionSelect.Null;
                }
                break;

            case OptionSelect.Null:
                //  オプションを選択
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
        //  オプションを開く
        m_isOption = true;
        //  シャッターの位置を上にする
        m_backImage.transform.localPosition = new Vector3(0.0f, 1080.0f, 0.0f);
        //  表示
        m_backImage.SetActive(true);
        //  UIも表示
        m_pauseTitle.SetActive(true);
        m_pauseTitle.transform.localPosition = new Vector3(0.0f, -225.0f, 0.0f);
        //  下に向けて
        m_backImage.transform.DOLocalMoveY(200.0f, 0.3f).SetEase(Ease.Linear);

        m_selectNum = 0;
        m_selectIcon.transform.localPosition = m_iconPoses[m_selectNum];

        //  プレイシーン以外ならセレクトシーンに戻るを半透明（選択不能）
        if (m_nowScene == AllScene.PlayScene) return;

        //  半透明にする
        Color color = m_selectImages[(int)OptionSelect.StageSelect].color;
        color.a = 0.5f;
        m_selectImages[(int)OptionSelect.StageSelect].color = color;
    }
    private void CloseOption()
    {
        //  オプションを閉じる
        m_isOption = false;
        m_pauseTitle.SetActive(false);

        //  色を戻す
        Color color = m_selectImages[(int)OptionSelect.StageSelect].color;
        color.a = 1.0f;
        m_selectImages[(int)OptionSelect.StageSelect].color = color;

        //  アイコンの色を変える
        BackColor();
        //  選択を失くす
        m_optionSelect = OptionSelect.Null;

        //  確認画面非表示
        m_confirmation.SetActive(false);
    }
    private void BackColor()
    {
        //  色を変える
        Color color = m_selectIconImage.color;
        color.r = 0f;
        color.b = 1f;
        m_selectIconImage.color = color;
    }
    private void YNSelect()
    {
        //  サイズ変更
        m_YNSelectObjs[m_YNnum].transform.localScale = Vector3.one + (new Vector3(0.05f, 0.05f, 0.0f) * Mathf.Sin(m_radian));
        m_radian += Mathf.PI / 180.0f;

        //  入力
        float moveX = m_inputActions.Option.MoveX.ReadValue<float>();
        if (Mathf.Abs(moveX) < m_deadZone) return;

        //  位置を変える
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
    //  オプションが画面での更新処理
    public void OptionSelectUpdate()
    {
        //  戻る
        if(m_inputActions.Option.Back.WasPressedThisFrame())
        {
            //  シャッターが上がる
            ExitOption();
            return;
        }
        //  選択
        if (m_inputActions.Option.Decide.WasPressedThisFrame())
        {
            m_audioSource.PlayOneShot(m_decideAudio);
            //  色を変える
            Color color = m_selectIconImage.color;
            color.r = 1f;
            color.b = 0f;
            m_selectIconImage.color = color;

            switch ((OptionSelect)m_selectNum)
            {

                case OptionSelect.BGM:
                    //  BGM制御へ
                    m_optionSelect = OptionSelect.BGM;
                    break;
                case OptionSelect.SE:
                    //  SE制御へ
                    m_optionSelect = OptionSelect.SE;
                    break;
                case OptionSelect.StageSelect:
                    //  ステージセレクト確認
                    m_optionSelect = OptionSelect.StageSelect;
                    //  確認ボタンの位置
                    m_confirmation.transform.localPosition = Vector3.zero;
                    //  戻るか確認
                    m_confirmation.SetActive(true);
                    //  選択を×
                    m_YNnum = 0;
                    break;
                case OptionSelect.End:
                    //  終了確認
                    m_optionSelect = OptionSelect.End;
                    //  確認ボタンの位置
                    m_confirmation.transform.localPosition = new Vector3(0.0f, -130.0f, 0.0f);
                    //  終了するか確認
                    m_confirmation.SetActive(true);
                    //  選択を×
                    m_YNnum = 0;
                    break;
            }
            return;
        }

        float move = m_inputActions.Option.MoveY.ReadValue<float>();

        //  入力がない
        if (Mathf.Abs(move) < m_deadZone)
        {
            m_timer = 0f;
            return;
        }
        //  入力のクールタイムがある
        if (m_timer > 0f)
        {
            m_timer -= Time.deltaTime;
            return;
        }

        m_audioSource.PlayOneShot(m_moveAudio);

        //  下向き
        if (move > 0f)
        {
            m_selectNum++;
            //  プレイシーンではないなら飛ばす
            if (m_nowScene != AllScene.PlayScene && (OptionSelect)m_selectNum == OptionSelect.StageSelect) m_selectNum++;
        }
        //  上向き
        else
        {
            m_selectNum--;
            //  プレイシーンではないなら飛ばす
            if (m_nowScene != AllScene.PlayScene && (OptionSelect)m_selectNum == OptionSelect.StageSelect) m_selectNum--;
        }

        //  選択値の範囲
        if (m_selectNum > (int)OptionSelect.End) m_selectNum = (int)OptionSelect.End;
        else if (m_selectNum < (int)OptionSelect.BGM) m_selectNum = (int)OptionSelect.BGM;

        //  実際にアイコンを動かす
        m_selectIcon.transform.localPosition = m_iconPoses[m_selectNum];

        //  クールタイム
        m_timer = m_coolTime;
    }
    //BGM
    public void SetAudioMixerBGM(float value)
    {
        //  -80~20の間
        var volume = Mathf.Lerp(-80f, 20f, value);
        //audioMixerに代入
        m_audioMixer.SetFloat("BGMVol", volume);
    }
    //SE
    public void SetAudioMixerSE(float value)
    {
        //  -80~20の間
        var volume = Mathf.Lerp(-80f, 20f, value);
        //audioMixerに代入
        m_audioMixer.SetFloat("SEVol", volume);
    }
    //  シャッター下がる
    public void StartSyutterDown(float time)
    {
        m_audioSource.PlayOneShot(m_downClipAudio);

        m_backImage.SetActive(true);
        m_pauseTitle.SetActive(false);
        //  初期化
        m_fadeFinish = false;

        m_backImage.transform.localPosition = new Vector3(0.0f, 1080.0f, 0.0f);

        var doT = DOTween.Sequence()
                .Append(m_backImage.transform.DOLocalMoveY(0.0f, time))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  シャッター上がる
    public void StartSyutterOn(float time)
    {
        m_audioSource.PlayOneShot(m_downClipAudio);

        //  初期化
        m_fadeFinish = false;
        m_backImage.SetActive(true);
        m_pauseTitle.SetActive(false);

        m_backImage.transform.localPosition = new Vector3(0.0f, 0.0f, 0.0f);

        var doT = DOTween.Sequence()
                .Append(m_backImage.transform.DOLocalMoveY(1080.0f, time))
                .AppendCallback(() => m_backImage.SetActive(false))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  フェイドイン開始
    public void StartFadeIn(float time)
    {
        //  初期化
        m_fadeFinish = false;

        //  画像の透明度を１にする
        m_fadeImage.color = new Color(0f, 0f, 0f, 1f);
        m_fadeImage.gameObject.SetActive(true);

        var doT = DOTween.Sequence()
                .Append(m_fadeImage.DOFade(0f, time))
                .AppendCallback(() => m_fadeImage.gameObject.SetActive(false))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  フェイドアウト開始
    public void StartFadeOut(float time)
    {
        //  初期化
        m_fadeFinish = false;

        //  画像の透明度を１にする
        m_fadeImage.color = new Color(0f, 0f, 0f, 0f);
        m_fadeImage.gameObject.SetActive(true);

        var doT = DOTween.Sequence()
                .Append(m_fadeImage.DOFade(1f, time))
                .AppendCallback(() => m_fadeFinish = true);
    }
    //  フェイドの終了を渡す
    public bool GetFadeFinish()
    {
        return m_fadeFinish;
    }

    private void ExitOption()
    {
        m_inputWait = true;
        //  オプションを閉じる
        m_isOption = false;
        //  選択を失くす
        m_optionSelect = OptionSelect.Null;
        //  確認画面非表示
        m_confirmation.SetActive(false);
        //  色を戻す
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
