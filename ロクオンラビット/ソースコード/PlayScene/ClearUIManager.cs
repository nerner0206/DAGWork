using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using DG.Tweening;
using TMPro;

public enum ClearSelect
{
    Back = 0,
    ReStart,
    Next,

    OverID
};

public class ClearUIManager : MonoBehaviour
{
    //  数字画像素材
    [SerializeField, Header("数字画像素材")]
    private List<Sprite> m_numbers;

    /// <summary>
    /// クリアUI
    /// </summary>
    [SerializeField, Tooltip("背景画像")]
    private Image m_backImage;
    [SerializeField, Tooltip("タイトル画像マスク")]
    private Image m_titleImageMask;
    [SerializeField, Tooltip("タイトル画像")]
    private Image m_titleImage;
    [SerializeField, Tooltip("タイトル画像マスク")]
    private Image m_timeImageMask;
    [SerializeField, Tooltip("タイム画像")]
    private Image m_timeImage;

    [SerializeField, Tooltip("時間の画像")]
    private List<Image> m_timeImages;

    [SerializeField, Tooltip("選択画像")]
    private List<Image> m_selectImages;
    [SerializeField, Tooltip("テープ")]
    private List<Image> m_tapeImages;

    [SerializeField, Tooltip("アイコン操作音")]
    private AudioClip m_moveAudio;
    [SerializeField, Tooltip("決定音")]
    private AudioClip m_decideAudio;
    [SerializeField, Tooltip("ジングル音")]
    private AudioClip m_clearAudio;
    [SerializeField, Tooltip("クラッカー音")]
    private AudioClip m_crackerAudio;
    [SerializeField, Tooltip("噴出音")]
    private AudioClip m_pusyuAudio;
    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;

    [SerializeField, Header("入力デッドゾーン")]
    private float deadZone = 0.1f;
    [SerializeField, Header("入力クールタイム")]
    private float coolTime = 0.5f;

    //  コントローラー
    private PlayerControll m_controll;

    //  アニメーションの終了
    private bool m_animFin;

    //  入力番号
    private int m_controllNum;
    //  時間
    private float m_timer;
    //  角度
    private float m_radian;

    public void ClearDisplay(float clearTime, PlayerControll inputActions, int tapeNum)
    {
        //  入力を受け取る
        m_controll = inputActions;

        //  分を求める
        int m = (int)clearTime / 60;
        //  秒を求める
        int s = (int)clearTime - m * 60;

        //  分を更に１と１０の位に分ける
        int m_ten = m / 10;
        int m_one = m % 10;

        //  秒を更に１と１０の位に分ける
        int s_ten = s / 10;
        int s_one = s % 10;

        //  画像の変更
        m_timeImages[0].sprite = m_numbers[m_ten];
        m_timeImages[1].sprite = m_numbers[m_one];
        m_timeImages[2].sprite = m_numbers[s_ten];
        m_timeImages[3].sprite = m_numbers[s_one];

        //  初期化
        Init();

        //  透明度を戻す
        for (int i = 0; i < tapeNum; i++)
        {
            m_tapeImages[i].color = new Color(1f, 1f, 1f, 1f);
        }

        ////  ダイアログ表示
        var sequence = DOTween.Sequence()
            //  背景画像を下へ
            .Append(m_backImage.rectTransform.DOLocalMoveY(0.0f, 0.5f).SetEase(Ease.OutElastic))
            //  タイトル画像を左から描画
            .Append(m_titleImageMask.rectTransform.DOSizeDelta(new Vector2(455.0f, 151.2f), 1.0f))
            //  タイム画像を左から描画
            .Append(m_timeImageMask.rectTransform.DOSizeDelta(new Vector2(514.0f, 121.5f), 1.0f))
            //  テープ画像のサイズを大きくする
            .AppendCallback(() => m_tapeImages[0].rectTransform.sizeDelta = new Vector2(360.0f, 360.0f))
            .AppendCallback(() => m_tapeImages[1].rectTransform.sizeDelta = new Vector2(360.0f, 360.0f))
            .AppendCallback(() => m_tapeImages[2].rectTransform.sizeDelta = new Vector2(360.0f, 360.0f))
            //  テープ画像のサイズを戻す
            .Append(m_tapeImages[0].rectTransform.DOSizeDelta(new Vector2(312.0f, 312.0f), 0.2f))
            .Join(m_tapeImages[1].rectTransform.DOSizeDelta(new Vector2(312.0f, 312.0f), 0.2f))
            .Join(m_tapeImages[2].rectTransform.DOSizeDelta(new Vector2(312.0f, 312.0f), 0.2f));

        //  選択アイコンの描画
        sequence
            .Append(m_selectImages[0].DOFade(1f, 0.1f))
            .Append(m_selectImages[1].DOFade(1f, 0.1f))
            .Append(m_selectImages[2].DOFade(1f, 0.1f))
            .AppendCallback(() => m_animFin = true);
    }

    private void Init()
    {
        m_controllNum = (int)ClearSelect.Next;
        m_timer = 0f;

        //  背景画像の位置
        m_backImage.transform.localPosition = new Vector3(0.0f, 1000.0f, 0.0f);

        //  タイトルマスクのサイズを設定
        m_titleImageMask.rectTransform.sizeDelta = new Vector2(0.0f, 126.0f);
        //  タイムマスクのサイズを設定
        m_timeImageMask.rectTransform.sizeDelta = new Vector2(0.0f, 121.5f);

        //  テープのサイズを全て0にする
        for (int i = 0; i < m_tapeImages.Count; i++)
        {
            m_tapeImages[i].rectTransform.sizeDelta = Vector2.zero;
            m_tapeImages[i].color = new Color(1f, 1f, 1f, 0f);
        }
        //  選択項目画像の透明化
        for (int i = 0; i < m_selectImages.Count; i++)
        {
            m_selectImages[i].color = new Color(1f, 1f, 1f, 0f);
        }
        
        //  アニメーションを未終了へ
        m_animFin = false;

        m_radian = 0.0f;

        //  ジングルを鳴らす
        m_audioSource.PlayOneShot(m_clearAudio);
        m_audioSource.PlayOneShot(m_crackerAudio);
        m_audioSource.PlayOneShot(m_crackerAudio);
        m_audioSource.PlayOneShot(m_pusyuAudio);
    }

    public bool ClearUIUpdate()
    {
        if (!m_animFin) return false;

        m_radian += Mathf.PI / 180.0f * 1.5f;
        m_selectImages[m_controllNum].transform.localScale = Vector3.one + (new Vector3(0.1f, 0.1f, 0.1f) * Mathf.Sin(m_radian));

        //  値を入力
        float move = m_controll.PlaySceneUI.Move.ReadValue<float>();
        //  入力がある
        if (Mathf.Abs(move) > deadZone)
        {
            if(m_timer <= 0f)
            {
                m_audioSource.PlayOneShot(m_moveAudio);
                if (move > 0f) m_controllNum++;
                else m_controllNum--;

                if (m_controllNum > (int)ClearSelect.Next) m_controllNum = (int)ClearSelect.Next;
                else if (m_controllNum < (int)ClearSelect.Back) m_controllNum = (int)ClearSelect.Back;

                m_radian = 0.0f;

                m_timer = coolTime;
            }
            else
            {
                m_timer -= Time.deltaTime;
            }
        }
        else
        {
            m_timer = 0f;
        }

        //  決定
        if(m_controll.PlaySceneUI.Decide.WasPressedThisFrame())
        {
            m_audioSource.PlayOneShot(m_decideAudio);
            return true;
        }
        return false;
    }

    public int ClearSelectNum()
    {
        return m_controllNum;
    }
}
