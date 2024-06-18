using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using NaughtyAttributes;

public class MoveFloor : MonoBehaviour
{
    [SerializeField, Required("プレイヤーオブジェクトを設定してください")]
    private GameObject m_player;

    [BoxGroup("始点と終点のオブジェクト"), SerializeField, Tooltip("このオブジェクトのtransformが始点の位置")]
    private Transform m_startPoint;
    [BoxGroup("始点と終点のオブジェクト"), SerializeField, Tooltip("このオブジェクトのtransformが終点の位置")]
    private Transform m_endPoint;

    [SerializeField, Tooltip("1アニメーションにかかる時間")]
    private float m_loopTime;
    [SerializeField, Tooltip("足場のイージング補完")]
    private AnimationCurve m_curve;

    [SerializeField, Tooltip("移動足場の移動係数")]
    private float m_complement;

    //  プレイヤーが乗っているかどうか
    [ShowNonSerializedField] private bool m_onPlayer;

    //  物理挙動コンポーネント
    private Rigidbody2D m_rb;
    //  経過時間の計測
    private float m_measuringTime;
    //  足場が動いているかどうか
    private bool m_inAction;

    //  前フレームの足場の位置
    private Vector2 m_beforePosition;         

    void Start()
    {
        //  初期化が必要な変数の初期化
        m_rb             = this.GetComponent<Rigidbody2D>();
        m_measuringTime  = 0f;
        m_beforePosition = this.transform.position;
        m_inAction       = true;    ///debug

        //  StartPointへ配置
        m_rb.MovePosition(m_startPoint.localPosition);
    }

    void Update()
    {
        //  動作中でなければ処理しない
        if (!m_inAction) return;

        //  経過時間の更新
        m_measuringTime += Time.deltaTime;

        //  到着時間と経過時間の割合を計算
        float ratio = m_measuringTime / m_loopTime;

        //  Inspectorに設定したcurve通りに移動させる
        float value = m_curve.Evaluate(ratio);
        Vector2 destination;
        destination.x = Mathf.Lerp(m_startPoint.localPosition.x, m_endPoint.localPosition.x, value);
        destination.y = Mathf.Lerp(m_startPoint.localPosition.y, m_endPoint.localPosition.y, value);

        m_rb.MovePosition(destination);

        PlayerComplement(destination);

        m_beforePosition = destination;
    }

    /// <summary>
    /// プレイヤーが上に乗っているときの位置補正
    /// </summary>
    /// <param name="destination">移動後の位置</param>
    private void PlayerComplement(Vector2 destination)
    {
        //  プレイヤーが足場に乗っていなければ処理しない
        if (!m_onPlayer) return;

        //  移動量計算
        Vector2 amountOfMove = destination - m_beforePosition;

        //  x軸方向にプレイヤーを補正
        amountOfMove.y = 0f;
        Vector2 playerPosition = m_player.transform.position;
        //_player.GetComponent<Rigidbody2D>().velocity += amountOfMove * 20f;
        m_player.GetComponent<Rigidbody2D>().AddForce(amountOfMove * m_complement, ForceMode2D.Impulse);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.transform.CompareTag("Player"))
        {
            m_onPlayer = true;
        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.transform.CompareTag("Player"))
        {
            m_onPlayer = false;
        }
    }

    /// <summary>
    /// 足場をStartPointの位置から動かす
    /// </summary>
    public void StartMove()
    {
        m_inAction = true;
        m_measuringTime = 0f;
        m_rb.MovePosition(m_startPoint.localPosition);
    }

    /// <summary>
    /// 足場を動かす
    /// </summary>
    public void PlayMove()
    {
        m_inAction = true;
    }

    /// <summary>
    /// 足場を止める
    /// </summary>
    public void StopMove()
    {
        m_inAction = false;
    }
}
