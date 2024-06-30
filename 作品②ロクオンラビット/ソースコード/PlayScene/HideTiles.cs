using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class HideTiles : MonoBehaviour
{
    //  タイルマップ
    private Tilemap m_tilemap;
    //  隠れているかの真偽値
    private bool m_isHide;
    //  透明度
    private float m_alpha;

    //  スタート
    void Start()
    {
        //  コンポーネントの取得
        m_tilemap = this.GetComponent<Tilemap>();
        //  非隠れ中
        m_isHide = false;
        //  不透明
        m_alpha = 1f;
    }

    void Update()
    {
        //  隠れ中なら徐々に透明にする
        if (m_isHide)
            m_alpha -= Time.deltaTime;
        //  非隠れ中なら徐々に不透明にする
        else
            m_alpha += Time.deltaTime;

        //  透明度の範囲に納める
        m_alpha = Mathf.Clamp(m_alpha, 0f, 1f);

        //  透明度の変更
        m_tilemap.color = new Color(255f, 255f, 255f, m_alpha);
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        //  プレイヤーなら透明にする
        if (collision.transform.CompareTag("Player"))
        {
            m_isHide = true;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        //  プレイヤーなら不透明にする
        if (collision.transform.CompareTag("Player"))
        {
            m_isHide = false;
        }

    }
}
