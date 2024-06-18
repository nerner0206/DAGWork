using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class CheckPoint : MonoBehaviour
{
    [SerializeField] private float m_num;

    [SerializeField, Tooltip("マテリアル")]
    private Material m_material;

    //  接触記録
    private bool m_check = false;
    
    //  取得・渡す
    public bool GetSetCheck
    {
        get { return m_check; }
        set { m_check = value; }
    }

    private List<CheckPoint> m_checkPoints = new List<CheckPoint>();

    //  他のチェックポイントを受け取る
    private CheckPoint[] m_points;

    [ColorUsage(false, true)] public Color m_color1;
    [ColorUsage(false, true)] public Color m_color2;

    private Animator m_animator;

    private void Start()
    {
        m_animator = GetComponent<Animator>();
        m_material.EnableKeyword("_EMISSION");

        MatReset();
    }
    private void Update()
    {
        if (!m_check) return;
        m_material.SetFloat("_Point", m_num);
    }


    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  プレイヤー以外なら処理しない
        if (!collision.gameObject.CompareTag("Player") || m_check) return;

        //  チェックポイントを通った
        m_check = true;
        m_animator.SetBool("Check", m_check);
        //  アニメーションの変更
        //CheckAnimator(check);
        m_material.SetColor("_Color", m_color2);


        //  他のチェックポイントを通っていたら
        foreach (var point in m_checkPoints)
        {
            if (!point.GetSetCheck) continue;

            point.MatReset();
            
            //  終了
            break;
        }
    }

    public void MatReset()
    {
        m_check = false;
        m_animator.SetBool("Check", m_check);
        m_material.SetColor("_Color", m_color1);
    }

    public void AddCheckPoint(CheckPoint point)
    {
        m_checkPoints.Add(point);
    }

    public void CheckAnimator(bool flag)
    {
        gameObject.GetComponent<Animator>().SetBool("Check", flag);
    }
}
