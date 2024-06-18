using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class PreviewManager : MonoBehaviour
{
    //  カメラ
    [SerializeField] private GameObject preCam;
    //  拡大時間
    [SerializeField] private float SCALE_TIME = 0.5f;

    [SerializeField] private Canvas canvas;

    //  移動前の位置
    private static readonly Vector3 BEFORE_POS = new Vector3(1792.0f, 952.0f, 0.0f);
    //  移動後の位置
    private static readonly Vector3 AFTER_POS = new Vector3(960.0f, 540.0f, 0.0f);
    //  移動前の大きさ
    private static readonly Vector2 BEFORE_SIZE = new Vector2(256.0f, 256.0f);
    //  移動後の大きさ
    private static readonly Vector2 AFTER_SIZE = new Vector2(1080.0f, 1080.0f);

    //  フレーム
    [SerializeField] private GameObject previewFrame;
    [SerializeField] private GameObject previewBack;
    //  マスク
    [SerializeField] private GameObject previewMask;
    //  raw
    [SerializeField] private GameObject previewRaw;

    [SerializeField] private Ease ease;

    //  元の位置に移動する
    public void MoveBefore()
    {
        //  移動
        previewFrame.transform.DOMove(BEFORE_POS, SCALE_TIME).SetEase(ease);
        //  大きさ変更
        previewFrame.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);
        previewBack.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);
        previewMask.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);
        previewRaw.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);

        canvas.sortingOrder = 0;
    }
    //  中心に移動させる
    public void MoveAfter()
    {
        //  移動
        previewFrame.transform.DOMove(AFTER_POS, SCALE_TIME).SetEase(ease);
        //  大きさ変更
        previewFrame.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);
        previewBack.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);
        previewMask.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);
        previewRaw.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);

        canvas.sortingOrder = 2;
    }

    //  カメラを回転させる
    public void PreviewCamRot(Vector3 target)
    {
        preCam.transform.RotateAround(target, new Vector3(0, 1, 0), 0.1f);
    }
    //  更新処理
    public void PreviewUpdate()
    {

    }
}
