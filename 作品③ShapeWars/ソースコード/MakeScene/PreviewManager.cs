using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class PreviewManager : MonoBehaviour
{
    //  �J����
    [SerializeField] private GameObject preCam;
    //  �g�厞��
    [SerializeField] private float SCALE_TIME = 0.5f;

    [SerializeField] private Canvas canvas;

    //  �ړ��O�̈ʒu
    private static readonly Vector3 BEFORE_POS = new Vector3(1792.0f, 952.0f, 0.0f);
    //  �ړ���̈ʒu
    private static readonly Vector3 AFTER_POS = new Vector3(960.0f, 540.0f, 0.0f);
    //  �ړ��O�̑傫��
    private static readonly Vector2 BEFORE_SIZE = new Vector2(256.0f, 256.0f);
    //  �ړ���̑傫��
    private static readonly Vector2 AFTER_SIZE = new Vector2(1080.0f, 1080.0f);

    //  �t���[��
    [SerializeField] private GameObject previewFrame;
    [SerializeField] private GameObject previewBack;
    //  �}�X�N
    [SerializeField] private GameObject previewMask;
    //  raw
    [SerializeField] private GameObject previewRaw;

    [SerializeField] private Ease ease;

    //  ���̈ʒu�Ɉړ�����
    public void MoveBefore()
    {
        //  �ړ�
        previewFrame.transform.DOMove(BEFORE_POS, SCALE_TIME).SetEase(ease);
        //  �傫���ύX
        previewFrame.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);
        previewBack.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);
        previewMask.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);
        previewRaw.GetComponent<RectTransform>().DOSizeDelta(BEFORE_SIZE, SCALE_TIME).SetEase(ease);

        canvas.sortingOrder = 0;
    }
    //  ���S�Ɉړ�������
    public void MoveAfter()
    {
        //  �ړ�
        previewFrame.transform.DOMove(AFTER_POS, SCALE_TIME).SetEase(ease);
        //  �傫���ύX
        previewFrame.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);
        previewBack.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);
        previewMask.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);
        previewRaw.GetComponent<RectTransform>().DOSizeDelta(AFTER_SIZE, SCALE_TIME).SetEase(ease);

        canvas.sortingOrder = 2;
    }

    //  �J��������]������
    public void PreviewCamRot(Vector3 target)
    {
        preCam.transform.RotateAround(target, new Vector3(0, 1, 0), 0.1f);
    }
    //  �X�V����
    public void PreviewUpdate()
    {

    }
}
