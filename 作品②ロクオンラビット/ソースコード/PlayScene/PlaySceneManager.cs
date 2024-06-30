using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public enum PlaySceneState
{
    FadeIn,         //  フェイドイン
    StartBefore,    //  始まる前
    Playing,        //  プレイ中
    GameOver,       //  ゲームオーバー
    Clear,          //  クリア
    FadeOut          //  フェイドアウト
};

public class PlaySceneManager : SceneManagement
{
    //  プレイシーンの状態
    public static PlaySceneState m_sceneState = PlaySceneState.StartBefore;

    [SerializeField, Header("サウンドを管理するクラス")]
    private SoundManager m_soundManager;
    [SerializeField, Header("UIを管理するクラス")]
    private UIManager m_uiManager;
    [SerializeField, Header("プレイヤー")]
    private PlayerController m_player;
    [SerializeField, Header("ゴール")]
    private Goal m_goal;
    [SerializeField, Header("チェックポイント")]
    private CheckPoint[] m_checkPoints;
    [SerializeField, Header("収集テープ")]
    private Tape[] m_tapes;
    [SerializeField, Tooltip("ゴールエフェクト")]
    private ParticleSystem m_clear;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;

    //  プレイヤーの開始位置
    private Vector3 m_startPos;
    //  次のシーンの名前
    private string m_nextName;
    //  クリア時間
    private float m_clearTimer;
    //  プレイギミック
    private PlayGimmick[] m_playGimmicks;
    //  収集物の回収フラグ
    private bool[] m_tapeFlags;
    //  収集物の数
    private int m_tapeNum;

    //  入力
    private PlayerControll m_inputActions;
    //  オプションUI
    private OptionUI m_option;

    //  定数  //////////////////////////////////////////////////////////////////////////////////////////////
    //  シーンID（プレイシーン）
    private const AllScene PLAYSCENE = AllScene.PlayScene;

    //  スタート
    private void Start()
    {
        //  一旦次のステージの名前を格納しておく
        m_nextName = m_nextSceneNames[0];

        //  入力を受け取る
        m_inputActions = new PlayerControll();
        //  入力ON
        m_inputActions.Enable();

        //  オプションの生成と初期化
        if (OptionUI.GetInstance == null)
        {
            m_option = Instantiate(m_optionPrefab).GetComponent<OptionUI>();
            m_option.Init();
        }
        else m_option = OptionUI.GetInstance.GetComponent<OptionUI>();
        //  オプションを初期化する
        m_option.Initialized(PLAYSCENE, m_inputActions);

        //  SoundManagerの初期化
        m_soundManager.SoundManagerInit(m_player.transform);
        //  UIManagerの初期化
        m_uiManager.UIManagerInit(m_player.gameObject.GetComponent<PlayerHaveSound>(), m_inputActions);

        //  プレイヤーの開始位置を記録
        m_startPos = m_player.transform.position;
        //  プレイヤーの初期化
        m_player.Init(m_inputActions);
        //  プレイヤーの非アクティブ
        m_player.gameObject.SetActive(false);

        //  チェックポイント同士を渡す
        for (int i = 0; i < m_checkPoints.Length; i++)
        {
            for (int j = 0; j < m_checkPoints.Length; j++)
            {
                //  同じなら処理しない
                if (m_checkPoints[i] == m_checkPoints[j]) continue;

                m_checkPoints[i].AddCheckPoint(m_checkPoints[j]);
            }
        }

        //  PlayGimmickをすべて取得
        m_playGimmicks = GameObject.FindObjectsOfType<PlayGimmick>();

        //  初期化
        m_tapeFlags = new bool[m_tapes.Length];
        TapeFlagReset();

        //  タイマーの初期化
        m_clearTimer = 0f;
        m_clear.gameObject.SetActive(false);

        m_audioSource.Play();

        //  状態を'フェイドイン'
        m_sceneState = PlaySceneState.FadeIn;
        //  フェイドインを開始する
        m_option.StartSyutterOn(m_fadeTime);
    }

    //  更新
    private void Update()
    {
        //  オプションを開いている時は処理しない
        if (OptionUI.m_isOption)
        {
            m_uiManager.Non();
            return;
        }

        //  SoundManagerの更新
        m_soundManager.SoundManagerUpdate();

        //  シーンの状態による処理
        switch (m_sceneState)
        {
            //  フェイドイン
            case PlaySceneState.FadeIn:
                //  フェイドインの終了判定を取る
                bool flag = m_option.GetFadeFinish();
                //  終了していないなら処理しない
                if (!flag) return;

                //  開始前へ
                m_sceneState = PlaySceneState.StartBefore;
                //  プレイヤーを表示
                m_player.gameObject.SetActive(true);
                //uiManager.FadeInStart();
                break;

            //  開始前
            case PlaySceneState.StartBefore:

                //  開始の判定を取る
                bool startFlag = m_player.GetIsStart();
                //  スポーンアニメーションが終了していないなら処理しない
                if (!startFlag) return;

                //  状態を'プレイ中'へ
                m_sceneState = PlaySceneState.Playing;
                break;

            case PlaySceneState.Playing:
                m_uiManager.On();
                //  ゴール判定(処理を一度終わらせる)→ゴールしたときの処理はGoal()内に記述
                if (IsGoal()) return;

                //  時間を追加する
                m_clearTimer += Time.deltaTime;
                //  収集アイテムの取得
                for (int i = 0; i < m_tapes.Length; i++)
                {
                    if (!m_tapes[i].GetSetTape) continue;

                    //  非表示
                    m_tapes[i].GetSetTape = false;
                    m_tapes[i].gameObject.SetActive(false);
                    //  取得状態
                    m_tapeFlags[m_tapeNum] = true;
                    //  UIを設定
                    m_uiManager.SetTapeUI(m_tapeFlags);
                    m_tapeNum++;
                }

                //  ゲームオーバー判定(処理を一度終わらせる)→ゲームオーバーしたときの処理はIsGameOver()内に記述
                if (IsGameOver()) return;

                //  UIManagerの更新（Restart）
                if (m_uiManager.UIUpdate())
                {
                    m_sceneState = PlaySceneState.GameOver;
                    //  フェイド開始
                    m_uiManager.FadeOutStart();
                    return;
                }
                break;

            case PlaySceneState.GameOver:
                //  メモ：暗転する時間を考慮していない→考慮する場合アニメーション内で呼び出す関数のタイミングを変える
                if(m_uiManager.ReStart())
                {
                    //  リスタート
                    ReStart();
                    //  状態を戻す
                    m_sceneState = PlaySceneState.StartBefore;

                    m_uiManager.FadeInStart();
                }
                break;

            case PlaySceneState.Clear:
                //  プレイヤーのクリア更新
                m_player.PlayerClear();
                //  UIManagerの更新
                bool decide = m_uiManager.ClearUIUpdate();
                //  決定していない
                if (!decide) return;

                //  決定した番号を取得
                int selectNum = m_uiManager.ClearUISelectNumber();
                //  番号による処理
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

    //  音の再生
    private void PlayAudio()
    {
        m_audioSource.Play();
    }

    //  ゴール判定
    private bool IsGoal()
    {
        //  ゴールしたか取得
        bool goalFlag = m_goal.GetSetIsGoal;
        //  ゴールしてなれば処理しない
        if (!goalFlag) return false;

        //  状態をクリアへ
        m_sceneState = PlaySceneState.Clear;
        m_audioSource.Stop();
        Invoke("PlayAudio", 5.0f);
        m_uiManager.Non();
        //  クリアUIを表示
        m_uiManager.Clear(m_clearTimer, m_tapeNum);
        m_clear.gameObject.SetActive(true);
        m_clear.Play();
        m_player.PlayerClearInit(m_goal.transform.position);
        return true;
    }

    //  ゲームオーバー判定
    private bool IsGameOver()
    {
        //  ゲームオーバーしたか取得
        bool gameOverFlag = m_player.GetIsGameOver();
        //  ゲームオーバーしてなれば処理しない
        if (!gameOverFlag) return false;
        
        //  状態を'ゲームオーバー'へ
        m_sceneState = PlaySceneState.GameOver;

        //  フェイド開始
        m_uiManager.FadeOutStart();

        return true;
    }

    //  クリア後処理
    private void AfterClearUpdate(ClearSelect clearSelect)
    {
        m_clear.gameObject.SetActive(false);
        CancelInvoke();
        switch (clearSelect)
        {
            //  ステージセレクトに戻る
            case ClearSelect.Back:
                m_nextName = m_nextSceneNames[0];

                NextScene();
                break;

            //  もう一度同じステージをPlay
            case ClearSelect.ReStart:
                //  リセット
                ClearReset();
                //  状態を戻す
                m_sceneState = PlaySceneState.GameOver;
                m_uiManager.FadeOutStart();
                break;

            //  次のステージへ
            case ClearSelect.Next:
                m_nextName = m_nextSceneNames[1];

                NextScene();
                break;
        }
    }

    //  リスタート
    private void ReStart()
    {
        //  プレイヤーの位置を戻す
        PlayerReset(true);
        //  プレイギミックをリセット
        PlayGimmickReset();
    }

    //  リセット
    private void ClearReset()
    {
        //  プレイヤーを最初から
        PlayerReset(false);
        //  プレイギミックをリセット
        PlayGimmickReset();
        m_audioSource.Play();
        m_uiManager.On();
        //  時間をリセット
        m_clearTimer = 0f;
        //  全てのチェックポイントをリセット
        if(m_checkPoints != null)
        {
            for (int i = 0; i < m_checkPoints.Length; i++)
            {
                //  全てfalseに
                m_checkPoints[i].GetSetCheck = false;
                //  アニメータをfalseで再生
                m_checkPoints[i].CheckAnimator(false);
            }
        }
        //  ゴールをfalse
        m_goal.GetSetIsGoal = false;
        //  リザルトを非表示
        m_uiManager.ClearReset();
    }

    //  プレイヤーリセット
    private void PlayerReset(bool checkpoint)
    {
        //  最初から又はチェックポイントが存在しない
        if (!checkpoint || m_checkPoints == null)
        {
            m_player.PlayerReset(m_startPos);
            return;
        }

        //  チェックポイントから
        //  プレイヤーの位置を戻す

        bool flag = false;

        for (int i = 0; i < m_checkPoints.Length; i++)
        {
            flag = m_checkPoints[i].GetSetCheck;
            if (!flag) continue;

            //  trueのチェックポイントから
            m_player.PlayerReset(m_checkPoints[i].transform.position);
            break;
        }
        //  チェックポイントを一つも通ってなければ最初から
        if (!flag) m_player.PlayerReset(m_startPos);
    }

    //  プレイギミックリセット
    private void PlayGimmickReset()
    {
        //  数だけ回す
        for (int i = 0; i < m_playGimmicks.Length; i++)
        {
            //  非表示になっているものは表示しなおす
            if (!m_playGimmicks[i].gameObject.activeSelf) m_playGimmicks[i].gameObject.SetActive(true);
            //  リセットする
            m_playGimmicks[i].GetComponent<PlayGimmick>().GimmickReset();
        }
    }

    //  収集物のリセット
    private void TapeFlagReset()
    {
        for (int i = 0; i < m_tapes.Length; i++)
        {
            m_tapes[i].gameObject.SetActive(true);
            m_tapeFlags[i] = false;
        }

        m_tapeNum = 0;
    }

    //  オプションを開ける判定の取得
    public override bool NonOptionState()
    {
        //  プレイ中以外は開けない
        if (m_sceneState != PlaySceneState.Playing) return true;
        return false;
    }

    //  次のシーン
    private void NextScene()
    {
        m_option.StartSyutterDown(m_fadeTime);
        //  状態を'開始前'
        m_sceneState = PlaySceneState.FadeOut;
    }
}
