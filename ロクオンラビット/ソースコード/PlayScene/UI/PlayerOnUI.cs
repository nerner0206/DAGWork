using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerOnUI : MonoBehaviour
{
    //  表示判定
    public bool display = false;

    [SerializeField, Header("表示時間")]
    private float m_displayTime = 1f;

    //  タイマー
    private float m_timer = 0;

    public void Start()
    {
        //  表示時間
        m_timer = m_displayTime;

        //  画像コンポーネントを取得
        Image image = gameObject.GetComponent<Image>();
        Color color = image.color;
        //  透明度を戻す
        color.a = 1f;
        image.color = color;
    }

    private void Update()
    {
        //  表示しない
        if (display) return;

        //  表示時間を減らす
        if (m_timer > 0f)
        {
            m_timer -= Time.deltaTime;
            return;
        }

        //  画像コンポーネントを取得
        Image image = gameObject.GetComponent<Image>();
        Color color = image.color;
        if (image.color.a > 0f)
        {
            //  徐々に透明に
            color.a -= Time.deltaTime;
            image.color = color;
        }
        else
        {
            //  非表示
            gameObject.SetActive(false);

            Start();
        } 
    }
}
