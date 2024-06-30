using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SelectStageManager : SceneManagement
{
    //  セレクトシーンの状態
    private enum SelectStageState
    {
        FadeIn,
        Main,
        FadeOut
    };

    [SerializeField, Header("マップの要素")]
    private Map[] m_maps;
    [SerializeField, Header("マップアイコンの位置")]
    private Transform m_iconTransform;
    [SerializeField, Header("マップアイコンの移動先")]
    private Transform[] m_iconMoves;
    [SerializeField, Header("選択UI")]
    private SelectUI m_selectUI;

    [SerializeField, Tooltip("アイコン操作音")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("決定音")]
    private AudioClip m_decideAudio;
    [SerializeField, Tooltip("AudioSource")]
    private AudioSource audioSource;
    [SerializeField, Tooltip("BGMAudioSource")]
    private AudioSource bgmAudioSource;

    [SerializeField, Tooltip("入力時間制限")]
    private float inputTime = 0.3f;

    //  コントローラー
    private PlayerControll m_controll;
    //  このシーン
    const AllScene m_thisScene = AllScene.SelectScene;
    //  設定
    private OptionUI m_option;
    //  シーンの状態
    private SelectStageState m_sceneState;
    //  選択肢番号
    private int m_mapNum;

    //  入力タイマー
    private float m_inputTimer;
    //  次のシーン
    private string m_nextScene;

    //  初期音量の定数
    const float INIT_BGM_VOLUME = 0.2f;

    //  初期化
    private void Start()
    {
        m_nextScene = m_nextSceneNames[0];

        //  入力の生成
        m_controll = new PlayerControll();
        m_controll.Enable();

        //  オプションの生成と初期化
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        m_option.Initialized(m_thisScene, m_controll);

        //  最初の位置
        m_mapNum = 0;
        //  アイコンの位置を変更
        SetIconPos(m_mapNum);
        //  UIの設定
        m_selectUI.SetUI(m_mapNum);

        //  タイマーの初期化
        m_inputTimer = 0f;

        //  音量
        bgmAudioSource.volume = INIT_BGM_VOLUME;

        //  フェイドイン状態にする
        m_sceneState = SelectStageState.FadeIn;
        //  フェイドインを開始する
        m_option.StartSyutterOn(m_fadeTime);
    }
    //  更新処理
    private void Update()
    {
        //  オプションを開いている時は処理しない
        if (OptionUI.m_isOption) return;

        switch (m_sceneState)
        {
            case SelectStageState.FadeIn:
                //  フェイドインの終了を取得
                bool flag = m_option.GetFadeFinish();
                //  終了していない
                if (!flag) break;

                //  終了したら次の状態へ
                m_sceneState = SelectStageState.Main;
                break;
            case SelectStageState.Main:
                //  処理
                MainUpdate();

                break;
            case SelectStageState.FadeOut:
                bgmAudioSource.volume -= Time.deltaTime;
                //  フェイドアウトの終了を受け取る
                flag = m_option.GetFadeFinish();

                if (!flag) break;

                //  オプションの画面遷移処理
                m_option.Finish();
                //  セレクトシーンへ移動する
                SceneManager.LoadScene(m_nextScene);
                break;
        }
    }

    private void MainUpdate()
    {
        //  決定ボタンが押されたら
        if(m_controll.Select.Decide.WasPressedThisFrame())
        {
            audioSource.PlayOneShot(m_decideAudio);
            m_nextScene = m_nextSceneNames[m_mapNum];
            //  フェイドアウトを開始
            m_option.StartSyutterDown(m_fadeTime);
            //  状態をフェイドアウトへ
            m_sceneState = SelectStageState.FadeOut;
            //  処理終了
            return;
        }

        //  バックボタンを押されたら
        if (m_controll.Option.Back.WasPressedThisFrame() && !m_option.GetInputWait())
        {
            //  タイトルシーン
            m_nextScene = "TitleScene";

            //  フェイドアウトを開始
            m_option.StartSyutterDown(m_fadeTime);
            //  状態をフェイドアウトへ
            m_sceneState = SelectStageState.FadeOut;
            //  処理終了
            return;
        }

        //  移動入力を受け取る
        float moveX = m_controll.Select.MoveX.ReadValue<float>();
        //  入力が小さい時は処理しない
        if (Mathf.Abs(moveX) < 0.3f)
        {
            //  タイマーの初期化
            m_inputTimer = 0.0f;
            return;
        }

        //  入力制限時間を減らす
        if (m_inputTimer > 0.0f) m_inputTimer -= Time.deltaTime;

        //  入力が下向きで"終了"にいない
        if (moveX > 0f && m_inputTimer <= 0f)
        {
            audioSource.PlayOneShot(m_moveAudio);
            //  次の選択項目へ
            m_mapNum++;
            //  最大数を超えたら
            if (m_mapNum > m_maps.Length - 1) m_mapNum = 0;
            //  選択項目を設定
            SetIconPos(m_mapNum);
            //  UIを設定
            m_selectUI.SetUI(m_mapNum);
            //  入力制限時間を設定
            m_inputTimer = inputTime;
        }
        //  入力が上向きで"開始"にいない
        else if (moveX < 0f && m_inputTimer <= 0f)
        {
            audioSource.PlayOneShot(m_moveAudio);
            //  前の選択項目へ
            m_mapNum--;
            //  最低数を超えたら
            if (m_mapNum < 0) m_mapNum = m_maps.Length - 1;
            //  選択項目を設定
            SetIconPos(m_mapNum);
            //  UIを設定
            m_selectUI.SetUI(m_mapNum);
            //  入力制限時間を設定
            m_inputTimer = inputTime;
        }
    }

    private void SetIconPos(int num)
    {
        //  番号の位置を取得
        Vector3 pos = m_iconMoves[num].transform.position;
        //  位置を変更
        m_iconTransform.position = pos;

        //  マップマテリアルの変更
        for (int i = 0; i < m_maps.Length; i++)
        {
            //  アイコン上のマップのマテリアルのみ
            if (i == num)
            {
                m_maps[i].SetOnIcon();
                continue;
            }

            //  それ以外
            m_maps[i].SetRemoveIcon();
        }
    }

    //  オプションを開ける判定の取得
    public override bool NonOptionState()
    {
        //  フェイド中は開けない
        if (m_sceneState != SelectStageState.Main) return true;
        return false;
    }
}
