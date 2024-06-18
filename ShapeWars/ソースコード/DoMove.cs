using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class DoMove : MonoBehaviour
{
    //  �ړ�����
    [SerializeField] private float MOVE_TIME = 1.0f;
    //  �ړ����@
    [SerializeField] private Ease easeWay = Ease.Linear;

    //  �J�n�ʒu�Ɩ߂�ʒu
    public static readonly List<Vector3> SorEpos;

    //  ���[���h���W����̈ړ�
    public void DoTweenWorldMove(Vector3 tPos)
    {
        //  �ړ�������
        gameObject.transform.DOMove(tPos, MOVE_TIME).SetEase(easeWay);
    }
    public void DoTweenLocalMove(Vector3 tPos)
    {
        //  �ړ�������
        gameObject.transform.DOLocalMove(tPos, MOVE_TIME).SetEase(easeWay);
    }

    //  �T�C�Y�傫��
    public void DoTweenResize(Vector2 tSize, Ease ease)
    {
        gameObject.GetComponent<RectTransform>().DOSizeDelta(tSize, MOVE_TIME).SetEase(ease);
    }
}
