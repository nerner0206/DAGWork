using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConfigManager : MonoBehaviour
{
    //  設定ボタン
    [SerializeField] private GameObject configButton;
    //  閉じるボタン
    [SerializeField] private GameObject closeButton;
    //  対誤操作用パネル
    [SerializeField] private GameObject backPanel;

    //  設定ボタンを押したら
    public void PushConfigButton()
    {
        //  設定ボタンを非表示
        configButton.SetActive(false);
        //  パネルを表示
        backPanel.SetActive(true);

        //  時を止める
        Time.timeScale = 0.0f;
    }
    //  閉じるボタンを押したら
    public void PushCloseButton()
    {
        //  パネルを非表示
        backPanel.SetActive(false);
        //  設定ボタンを表示
        configButton.SetActive(true);

        //  時を動かす
        Time.timeScale = 1.0f;
    }

    //  ゲームを終了
    public void PushEndButton()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#else
    Application.Quit();
#endif
    }
}
