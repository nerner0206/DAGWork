using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MessageCollider : MonoBehaviour
{
    [SerializeField, TextArea, Tooltip("表示するメッセージ")]
    private string m_message;

    private PlaySceneText m_playSceneText;

    private bool m_once = false;

    private void Start()
    {
        //  シーンにあるPlaySceneTextスクリプトを取得
        m_playSceneText = FindObjectOfType<PlaySceneText>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  1度のみ実行
        if (m_once) return;

        //  プレイヤーがコライダーに当たったらテキストを表示する
        if (collision.transform.CompareTag("Player"))
        {
            m_playSceneText.TextStart(m_message);
            m_once = true;
        }
    }
}
