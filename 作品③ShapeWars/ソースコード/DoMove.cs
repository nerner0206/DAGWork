using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class DoMove : MonoBehaviour
{
    //  移動時間
    [SerializeField] private float MOVE_TIME = 1.0f;
    //  移動方法
    [SerializeField] private Ease easeWay = Ease.Linear;

    //  開始位置と戻る位置
    public static readonly List<Vector3> SorEpos;

    //  ワールド座標を上の移動
    public void DoTweenWorldMove(Vector3 tPos)
    {
        //  移動させる
        gameObject.transform.DOMove(tPos, MOVE_TIME).SetEase(easeWay);
    }
    public void DoTweenLocalMove(Vector3 tPos)
    {
        //  移動させる
        gameObject.transform.DOLocalMove(tPos, MOVE_TIME).SetEase(easeWay);
    }

    //  サイズ大きく
    public void DoTweenResize(Vector2 tSize, Ease ease)
    {
        gameObject.GetComponent<RectTransform>().DOSizeDelta(tSize, MOVE_TIME).SetEase(ease);
    }
}
