using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LogoSceneManager : SceneManagement
{
    //  タイトルシーンの状態
    private enum LogoSceneState
    {
        FadeIn,
        Main,
        FadeOut
    };

    [SerializeField, Tooltip("表示時間")]
    private float displayTime = 1.0f;

    //  コントローラー
    private PlayerControll m_controll;
    //  このシーン
    const AllScene m_thisScene = AllScene.LogoScene;
    //  設定
    private OptionUI m_option;
    //  シーンの状態
    private LogoSceneState m_sceneState;
    //  タイマー
    private float m_timer;

    private void Start()
    {
        //  入力の生成
        m_controll = new PlayerControll();
        m_controll.Enable();

        //  オプションの生成と初期化
        //  オプションの生成と初期化
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        m_option.Initialized(m_thisScene, m_controll);

        m_timer = displayTime;

        //  フェイドイン状態にする
        m_sceneState = LogoSceneState.FadeIn;
        //  フェイドインを開始する
        m_option.StartFadeIn(m_fadeTime);
    }

    private void Update()
    {
        //  オプションを開いている時は処理しない
        if (OptionUI.m_isOption) return;

        switch(m_sceneState)
        {
            case LogoSceneState.FadeIn:
                //  フェイドインの終了を取得
                bool flag = m_option.GetFadeFinish();
                //  終了していない
                if(!flag) break;

                //  終了したら次の状態へ
                m_sceneState = LogoSceneState.Main;
                break;
            case LogoSceneState.Main:
                //  処理
                MainUpdate();
                
                break;
            case LogoSceneState.FadeOut:
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
        if(m_timer > 0.0f)
        {
            m_timer -= Time.deltaTime;
            return;
        }

        m_sceneState = LogoSceneState.FadeOut;
        //  フェイドインを開始する
        m_option.StartSyutterDown(0.5f);
    }

    //  オプションを開ける判定の取得
    public override bool NonOptionState()
    {
        //  常に開けない
        return true;
    }
}
