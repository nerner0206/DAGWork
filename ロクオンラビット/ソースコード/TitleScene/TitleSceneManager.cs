using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleSceneManager : SceneManagement
{
    //  タイトルシーンの状態
    private enum TitleSceneState
    {
        FadeIn,
        Main,
        FadeOut
    };

    //  選択項目
    private enum SelectKind
    {
        Start,
        Option,
        Finish
    }

    [SerializeField, Tooltip("選択項目の位置")]
    private Transform[] m_selectTransforms;
    [SerializeField, Tooltip("選択アイコンの位置")]
    private Transform m_selectIconTransform;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;
    [SerializeField, Tooltip("BGMAudioSource")]
    private AudioSource m_bgmAudioSource;
    [SerializeField, Tooltip("アイコン操作")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("決定")]
    private AudioClip m_decideAudio;

    [SerializeField, Tooltip("入力時間制限")]
    private float inputTime = 0.3f;

    //  このシーン
    const AllScene m_thisScene = AllScene.TitleScene;

    //  コントローラー
    private PlayerControll m_controll;
    //  設定
    private OptionUI m_option;
    //  シーンの状態
    private TitleSceneState m_sceneState;
    //  選択の種類
    private SelectKind m_selectKind;

    //  入力タイマー
    private float m_inputTimer;

    private void Start()
    {
        //  入力の生成
        m_controll = new PlayerControll();
        m_controll.Enable();

        //  音量
        m_bgmAudioSource.volume = 0.2f;

        //  オプションの生成と初期化
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        //option = OptionUI.Instance.GetComponent<OptionUI>();
        m_option.Initialized(m_thisScene, m_controll);

        //  開始の上に置く
        SetSelectIcon(SelectKind.Start);

        //  タイマーの初期化
        m_inputTimer = 0f;

        //  フェイドイン状態にする
        m_sceneState = TitleSceneState.FadeIn;
        //  フェイドインを開始する
        m_option.StartSyutterOn(m_fadeTime);
    }

    private void Update()
    {
        //  オプションを開いている時は処理しない
        if (OptionUI.m_isOption) return;

        switch(m_sceneState)
        {
            case TitleSceneState.FadeIn:
                //  フェイドインの終了を取得
                bool flag = m_option.GetFadeFinish();
                //  終了していない
                if(!flag) break;

                //  終了したら次の状態へ
                m_sceneState = TitleSceneState.Main;
                break;
            case TitleSceneState.Main:
                //  処理
                MainUpdate();
                
                break;
            case TitleSceneState.FadeOut:
                m_bgmAudioSource.volume -= Time.deltaTime * 0.5f;
                //  フェイドアウトの終了を受け取る
                flag = m_option.GetFadeFinish();

                if (!flag) break;
                
                //  オプションの画面遷移処理
                m_option.Finish();
                //  セレクトシーンへ移動する
                SceneManager.LoadScene(m_nextSceneNames[0]);
                break;
        }
    }

    //  更新処理
    private void MainUpdate()
    {
        //  決定ボタンを押した時の処理
        if (m_controll.Title.Decide.WasPressedThisFrame())
        {
            m_audioSource.PlayOneShot(m_decideAudio);
            //  種類ごとにおける処理
            switch(m_selectKind)
            {
                //  開始
                case SelectKind.Start:
                    //  フェイドアウトを開始
                    m_option.StartSyutterDown(m_fadeTime);
                    //  状態をフェイドアウトへ
                    m_sceneState = TitleSceneState.FadeOut;
                    break;

                //  オプション
                case SelectKind.Option:
                    m_option.OpenOption();
                    break;

                //  終了
                case SelectKind.Finish:
                    //  とりあえず確認なしで終了させる
#if UNITY_EDITOR
                    UnityEditor.EditorApplication.isPlaying = false;//ゲームプレイ終了
#else
    Application.Quit();//ゲームプレイ終了
#endif
                    break;
            }
            //  処理終了
            return;
        }

        //  移動入力を受け取る
        float moveY = m_controll.Title.Select.ReadValue<float>();
        //  入力が小さい時は処理しない
        if (Mathf.Abs(moveY) < 0.3f)
        {
            //  タイマーの初期化
            m_inputTimer = 0.0f;
            return;
        }

        //  入力制限時間を減らす
        if (m_inputTimer > 0.0f) m_inputTimer -= Time.deltaTime;

        //  入力が下向きで"終了"にいない
        if(moveY < 0f && m_selectKind != SelectKind.Finish && m_inputTimer <= 0f)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            //  次の選択項目へ
            m_selectKind++;
            //  選択項目を設定
            SetSelectIcon(m_selectKind);
            //  入力制限時間を設定
            m_inputTimer = inputTime;
        }
        //  入力が上向きで"開始"にいない
        else if (moveY > 0f && m_selectKind != SelectKind.Start && m_inputTimer <= 0f)
        {
            m_audioSource.PlayOneShot(m_moveAudio);
            //  前の選択項目へ
            m_selectKind--;
            //  選択項目を設定
            SetSelectIcon(m_selectKind);
            //  入力制限時間を設定
            m_inputTimer = inputTime;
        }
    }
    //  選択項目の位置を設定する
    private void SetSelectIcon(SelectKind kind)
    {
        //  選択状態の変更
        m_selectKind = kind;
        //  位置を取得
        Vector3 pos = m_selectIconTransform.position;
        //  番号を取得
        int num = (int)m_selectKind;
        //  Y座標だけ移動させる
        pos.y = m_selectTransforms[num].position.y;
        //  位置を設定
        m_selectIconTransform.position = pos;
    }

    //  オプションを開ける判定の取得
    public override bool NonOptionState()
    {
        //  フェイド中は開けない
        if (m_sceneState != TitleSceneState.Main) return true;
        return false;
    }
}
