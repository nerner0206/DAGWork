using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BeltConveyor : MonoBehaviour
{
    [SerializeField, Tooltip("オブジェクトを押す力")]
    private float m_pushForce = 30f;

    [SerializeField, Tooltip("オブジェクトの目標速度")]
    private float m_TargetDriveSpeed = 3f;

    //  ベルトコンベアの稼働状況
    private bool m_isOn;
    //  移動速度
    private float m_moveSpeed;
    //  力の方向
    private Vector2 m_pushDir;

    //  接触したオブジェクト
    private List<Rigidbody2D> m_rigidbody2Ds;

    //  ベルトコンベアの稼働状況取得・設定
    public bool GetSetIsOn
    {
        get { return m_isOn; }
        set { m_isOn = value; }
    }

    public void Init(bool flag)
    {
        //  稼働状況
        m_isOn = flag;
        //  リストを初期化
        m_rigidbody2Ds = new List<Rigidbody2D>();

        m_moveSpeed = 0.0f;
    }

    private void FixedUpdate()
    {
        //  稼働していない・接触オブジェクトがないなら処理しない
        if (!m_isOn || m_rigidbody2Ds == null) return;

        //消滅したオブジェクトは除去する
        m_rigidbody2Ds.RemoveAll(r => r == null);
        if(m_rigidbody2Ds == null) return;

        foreach (var r in m_rigidbody2Ds)
        {
            //物体の移動速度のベルトコンベア方向の成分だけを取り出す
            var objectSpeed = Vector2.Dot(r.velocity, m_pushDir);

            //目標値以下なら加速する
            if (objectSpeed >= Mathf.Abs(m_TargetDriveSpeed)) continue;
            //  力を与える
            r.AddForce(m_pushDir * m_pushForce * m_moveSpeed, ForceMode2D.Force);
        }
    }

    //  オブジェクトが接触
    private void OnCollisionEnter2D(Collision2D collision)
    {
        //  コンポーネントを所持していない
        if (collision.gameObject.TryGetComponent(out Rigidbody2D rb2D))
        {
            //  追加
            m_rigidbody2Ds.Add(rb2D);

            rb2D.constraints = RigidbodyConstraints2D.FreezeRotation;
        }
    }
    //  オブジェクトが離れる
    private void OnCollisionExit2D(Collision2D collision)
    {
        //  コンポーネントを所持していない
        if (collision.gameObject.TryGetComponent(out Rigidbody2D rb2D))
        {
            //  削除
            m_rigidbody2Ds.Remove(rb2D);
        }
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        //  コンポーネントを所持していない
        if (collision.gameObject.TryGetComponent(out Rigidbody2D rb2D))
        {
            rb2D.constraints = RigidbodyConstraints2D.FreezeRotation;
        }
    }

    //  力の方向を設定する
    public void SetPushDir(float angle, float animSpeed)
    {
        //  方向（０度）
        Vector2 dir = Vector2.right;

        //  角度を設定
        m_pushDir.x = dir.x * Mathf.Cos(angle);
        m_pushDir.y = dir.x * Mathf.Sin(angle);

        //  アニメスピードを反映させる
        m_pushDir *= animSpeed;
        m_moveSpeed = Mathf.Abs(animSpeed);

        //  単位ベクトル
        m_pushDir.Normalize();
    }
}
