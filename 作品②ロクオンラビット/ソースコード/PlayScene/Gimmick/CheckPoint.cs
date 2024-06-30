using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class CheckPoint : MonoBehaviour
{
    [SerializeField] private float m_num;

    [SerializeField, Tooltip("�}�e���A��")]
    private Material m_material;

    //  �ڐG�L�^
    private bool m_check = false;
    
    //  �擾�E�n��
    public bool GetSetCheck
    {
        get { return m_check; }
        set { m_check = value; }
    }

    private List<CheckPoint> m_checkPoints = new List<CheckPoint>();

    //  ���̃`�F�b�N�|�C���g���󂯎��
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
        //  �v���C���[�ȊO�Ȃ珈�����Ȃ�
        if (!collision.gameObject.CompareTag("Player") || m_check) return;

        //  �`�F�b�N�|�C���g��ʂ���
        m_check = true;
        m_animator.SetBool("Check", m_check);
        //  �A�j���[�V�����̕ύX
        //CheckAnimator(check);
        m_material.SetColor("_Color", m_color2);


        //  ���̃`�F�b�N�|�C���g��ʂ��Ă�����
        foreach (var point in m_checkPoints)
        {
            if (!point.GetSetCheck) continue;

            point.MatReset();
            
            //  �I��
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
