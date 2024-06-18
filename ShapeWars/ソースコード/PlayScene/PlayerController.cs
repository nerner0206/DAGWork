using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using DG.Tweening;

//  プレイヤーの状態
public enum PlayerState
{
    Move,       //  移動状態
    Attack,     //  攻撃状態
    Avoidance,  //  回避状態
    Dead,       //  死亡状態
    Cool,       //  待機状態
    LockOn,     //  追跡状態

    OverID
}

public class PlayerController : MonoBehaviour
{
    //  プレイヤー状態
    private PlayerState playerState;
    //  アニメーター
    private Animator animator;

    //  回転する目標
    private Quaternion targetRotation;

    //  武器オブジェクト
    private GameObject weapon;
    //  武器の攻撃力
    private int weaponPower;

    //  プレイヤーの最大体力
    [SerializeField] private int MaxHP = 0;
    //  プレイヤーの体力
    private int hp;

    //  HPのUI
    [SerializeField] private Image GreenGauge;
    [SerializeField] private Image RedGauge;
    private Tween redGaugeTween;

    private bool muteki;
    private float mutekiTimer;
    [SerializeField] private float mutekiTime;

    //  エフェクト
    [SerializeField] private GameObject deadE;

    private bool dead;

    private Gamepad gamepad;

    //  初期化
    public void PlayerInit()
    {
        //  プレイヤー状態を移動へ
        playerState = PlayerState.Move;

        //  アニメーターコンポーネントを取得
        animator = gameObject.GetComponent<Animator>();

        //  武器を初期化
        weapon = new GameObject();
        //  武器の攻撃力を初期化
        weaponPower = 0;

        //  体力を入れる
        hp = MaxHP;

        //  初期化
        targetRotation = transform.rotation;

        muteki = false;
        mutekiTimer = 0.0f;

        dead = false;
    }

    //  更新処理
    public void PlayerUpdate()
    {
        //  処理しない条件(完全に死亡)
        if (playerState == PlayerState.Dead) return;

        //  体力が０以下＆まだ死んでいない
        if(hp <= 0 && playerState != PlayerState.Dead)
        {
            //  死亡状態へ
            playerState = PlayerState.Dead;
            //  死亡アニメーションの再生
            animator.SetTrigger("Dead");
            //  エフェクトを生成
            Instantiate(deadE, gameObject.transform.position, Quaternion.identity);
            return;
        }

        //  無敵状態にある
        if(muteki)
        {
            //  無敵時間を消費
            mutekiTimer -= Time.deltaTime;
            //  無敵を解除
            if (mutekiTimer <= 0.0f) muteki = false;
        }

        //  ゲームパッドを取得する
        gamepad = Gamepad.current;
        //  ゲームパッドが接続されていない場合処理しない
        if (gamepad == null) return;

        //  各状態の更新
        switch (playerState)
        {
            //  移動
            case PlayerState.Move:
                //  左スティックの入力情報を取得
                float LR = gamepad.leftStick.ReadValue().x;
                float TB = gamepad.leftStick.ReadValue().y;

                //  入力があったら移動する
                if (Mathf.Abs(LR) > 0.1f || Mathf.Abs(TB) > 0.1f)
                {
                    //  カメラの方向から正面ベクトルを計算
                    var horizontalRotation = Quaternion.AngleAxis(Camera.main.transform.eulerAngles.y, Vector3.up);
                    //  移動方向の計算
                    Vector3 velocity = horizontalRotation * new Vector3(LR, 0.0f, TB).normalized;
                    //  移動速度の計算
                    var speed = gamepad.leftTrigger.ReadValue() > 0.8f ? 1.0f : 0.5f;
                    //  回転速度の計算
                    var rotationSpeed = 600 * Time.deltaTime;

                    //  移動方向が十分に大きいとき回転量を決める
                    if (velocity.magnitude > 0.5f) targetRotation = Quaternion.LookRotation(velocity, Vector3.up);
                    //  実際に回転する
                    transform.rotation = Quaternion.RotateTowards(transform.rotation, targetRotation, rotationSpeed);
                    //  移動方向にアニメーションを再生
                    animator.SetFloat("Move", velocity.magnitude * speed, 0.1f, Time.deltaTime);
                }

                //  攻撃する
                if (gamepad.rightTrigger.ReadValue() > 0.7f)
                {
                    //  攻撃状態へ
                    playerState = PlayerState.Attack;
                    //  攻撃アニメーションの再生
                    animator.SetTrigger("Attack");
                    return;
                }

                //  回避する
                if(gamepad.buttonNorth.wasPressedThisFrame)
                {
                    //  回避状態へ
                    playerState = PlayerState.Avoidance;
                    //  回避アニメーションの再生
                    animator.SetTrigger("Avoidance");
                    return;
                }

                //  ロックオン状態にする
                if (gamepad.buttonWest.wasPressedThisFrame)
                {
                    //  ロックオン状態へ
                    playerState = PlayerState.LockOn;
                    return;
                }

                break;
            //  攻撃
            case PlayerState.Attack:

                break;
            //  回避
            case PlayerState.Avoidance:

                break;
            //  追跡
            case PlayerState.LockOn:

                break;
            //  待機
            case PlayerState.Cool:

                break;
        }
    }

    //  死亡アニメーションの終了
    void Dead()
    {
        //  完全に死亡した状態にする
        dead = true;
    }
    //  武器を振り終わったら攻撃状態を解除する
    void AttackAnimFinish()
    {
        //  クール状態にする
    }

    //  武器オブジェクトを取得
    public void SetWeaponObject(GameObject weapon)
    {
        this.weapon = weapon;
    }
    //  プレイヤー状態を渡す
    public PlayerState GetPlayerState()
    {
        return playerState;
    }
    //  アニメーション速度
    public void SetAnimSpeed(float ratio)
    {
        animator.SetFloat("AnimSpeed", Mathf.Lerp(1.2f, 0.8f, ratio));
    }
    //  攻撃力を設定
    public void SetAttackPower(float ratio)
    {
        weaponPower = (int)Mathf.Lerp(100.0f, 300.0f, ratio);
    }
    //  攻撃力を渡す
    public int GetAttackPower()
    {
        return weaponPower;
    }

    //  攻撃を受けた
    public void Damaged(int damage)
    {
        //  UIの変更
        GaugeReduction((float)damage);
        //  ダメージ分受ける
        hp -= damage;

        //  被ダメアニメーションの再生
        animator.SetTrigger("hit");

        //  攻撃中だったら移動に変更する
        if (playerState == PlayerState.Attack) playerState = PlayerState.Move;

        muteki = true;
        mutekiTimer = mutekiTime;
    }

    public bool Muteki()
    {
        return muteki;
    }

    private void GaugeReduction(float reducationValue, float time = 1f)
    {
        var valueFrom = (float)hp / (float)MaxHP;
        var valueTo = ((float)hp - reducationValue) / (float)MaxHP;

        // 緑ゲージ減少
        GreenGauge.fillAmount = valueTo;

        if (redGaugeTween != null)
        {
            redGaugeTween.Kill();
        }

        // 赤ゲージ減少
        redGaugeTween = DOTween.To(
            () => valueFrom,
            x => {
                RedGauge.fillAmount = x;
            },
            valueTo,
            time
        );
    }
}
