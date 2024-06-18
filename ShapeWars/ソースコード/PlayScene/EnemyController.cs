using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

//  敵の種類
public enum EnemyKind
{
    Enemy01,
    Enemy02,
    Enemy03,
    Enemy04
}
//  敵の状態
public enum EnemyState
{
    Create,
    Move,
    Attack,
    HitStop,
    Blow,
    Dead
}

//  敵のステータスクラス
[System.Serializable]
public class EnemyStatus
{
    public EnemyKind kind;
    public EnemyState state;
    public int hp;
    public float speed;
    public int power;
}

public class EnemyController : MonoBehaviour
{
    //  RigidBody
    private Rigidbody rd;

    //  敵のステータス
    [SerializeField] private EnemyStatus enemyStatus;

    //  最大HP
    private int MaxHP;

    //  プレイヤーの情報を所持
    private GameObject player;
    //  プレイヤースクリプト
    private PlayerController playerController;
    //  目標（プレイヤー）の情報
    private Transform target;
    //  プレイヤーとの距離
    private Vector2 dis;

    //  攻撃を受けた
    private bool hit;
    //  攻撃を一回分だけ与える
    private bool attacked;

    //  敵が死んだ
    public bool IsDead { get; set; }

    //  ヒットストップ時間
    [SerializeField] private float HITSTOP_TIME;
    //  ヒットストップカウンタ
    private float hitStopTimer;

    //  ぶっ飛ぶ方向
    private Vector3 vel;

    //  被ダメエフェクト
    [SerializeField] private GameObject hitEffect;
    [SerializeField] private GameObject deadHitEffect;
    //  死亡エフェクト
    [SerializeField] private GameObject deadEffect;

    //  HPのUI
    [SerializeField]
    private Image GreenGauge;
    [SerializeField]
    private Image RedGauge;

    private Tween redGaugeTween;

    private AudioSource audioSource;

    //  初期化
    public void EnemyInit(GameObject Player)
    {
        //  コンポーネント取得
        rd = gameObject.GetComponent<Rigidbody>();
        gameObject.GetComponent<TrailRenderer>().enabled = false;
        //  最初の状態をStop
        enemyStatus.state = EnemyState.Create;

        MaxHP = enemyStatus.hp;

        //  プレイヤーオブジェクトを取得
        player = Player;
        //  プレイヤースクリプトを取得
        playerController = player.GetComponent<PlayerController>();
        //  プレイヤーのtransform情報を取得
        target = player.transform;
        //  距離を初期化
        dis = new Vector2();

        //  被攻撃状態をfalse
        hit = false;

        //  制限を全て失くす（重力の適応）
        rd.constraints = RigidbodyConstraints.None;

        //  攻撃していないのでfalse
        attacked = false;

        vel = new Vector3();

        hitStopTimer = 0.0f;

        IsDead = false;

        audioSource = gameObject.GetComponent<AudioSource>();
    }

    
    public void EnemyUpdate()
    {
        //  完全な死亡状態なら処理をしない
        if (enemyStatus.state == EnemyState.Dead) return;

        //  ステージ外に出た場合
        if (gameObject.transform.position.x > 30.0f ||
            gameObject.transform.position.x < -30.0f ||
            gameObject.transform.position.z > 30.0f ||
            gameObject.transform.position.z < -30.0f)
        {
            enemyStatus.state = EnemyState.Dead;
        }

            //  プレイヤーと敵の距離（Y座標は考えない）
            dis = new Vector2(target.position.x - gameObject.transform.position.x,
            target.position.z - gameObject.transform.position.z);

        //  移動方向ベクトルを正規化
        Vector2 velocity = dis.normalized;
        //  プレイヤーの方向を見る
        if (enemyStatus.state == EnemyState.Move) gameObject.transform.forward = new Vector3(velocity.x, 0.0f, velocity.y);

        //  被攻撃状態がtrue＆プレイヤーの状態が攻撃では無い
        if(hit && playerController.GetPlayerState() != PlayerState.Attack) hit = false;

        //  敵の状態における処理
        switch (enemyStatus.state)
        {
            case EnemyState.Create:

                break;
            case EnemyState.Move:
                //  正面方向のベクトルへ移動
                gameObject.GetComponent<Animator>().SetFloat("Move", gameObject.transform.forward.magnitude * enemyStatus.speed, 0.1f, Time.deltaTime);
                //  攻撃
                if (dis.magnitude < 2.5f)
                {
                    //  攻撃状態へ
                    enemyStatus.state = EnemyState.Attack;
                    //  攻撃アニメーションの再生
                    gameObject.GetComponent<Animator>().SetTrigger("Attack");
                }

                break;
            case EnemyState.Attack:

                break;
            case EnemyState.HitStop:
                
                //  揺らす


                //  時間をカウント
                hitStopTimer += Time.deltaTime;
                //  時間が小さいなら処理しない
                if (hitStopTimer < HITSTOP_TIME) return;

                //  リセット
                hitStopTimer = 0.0f;
                //  吹き飛ばす
                enemyStatus.state = EnemyState.Blow;
                //  アニメーションを進める
                gameObject.GetComponent<Animator>().speed = 0.5f;

                break;
            case EnemyState.Blow:
                gameObject.transform.position = gameObject.transform.position + (vel * Time.deltaTime);
                //  空中方向を０へ
                Vector3 sub = gameObject.transform.position;
                sub.y = 1.0f;
                gameObject.transform.position = sub;

                //  ステージ外に出た場合
                if(gameObject.transform.position.x > 30.0f ||
                    gameObject.transform.position.x < -30.0f ||
                    gameObject.transform.position.z > 30.0f ||
                    gameObject.transform.position.z < -30.0f)
                {
                    //  完全な死亡状態
                    enemyStatus.state = EnemyState.Create;

                    //  アニメーションを進める
                    gameObject.GetComponent<Animator>().speed = 1.0f;
                    //  死亡アニメーションの再生
                    gameObject.GetComponent<Animator>().SetTrigger("Dead");
                    //  死亡エフェクト
                    GameObject de = Instantiate(deadEffect);
                    de.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);
                    //  制限
                    rd.constraints = RigidbodyConstraints.FreezeAll;
                }

                break;

            case EnemyState.Dead:

                break;
        }
    }

    private void OnTriggerStay(Collider other)
    {
        //  プレイヤーからの攻撃判定
        //  当たったオブジェクトが武器＆プレイヤーが攻撃状態＆まだ当たっていない状態
        if(other.gameObject.CompareTag("PlayerWeapon") &&
            playerController.GetPlayerState() == PlayerState.Attack &&
            !hit)
        {
            //  当たった
            hit = true;
            audioSource.Play();

            //  攻撃力を取得
            int power = playerController.GetAttackPower();
            //  UIを減らす
            GaugeReduction((float)power);
            //  HPを攻撃力分消費
            enemyStatus.hp -= power;

            //  被ダメアニメーションの再生
            gameObject.GetComponent<Animator>().SetTrigger("Hit");
            //  エフェクトを出す
            GameObject he = Instantiate(hitEffect);
            he.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);

            //  体力が0以下になったら
            if (enemyStatus.hp <= 0)
            {
                //  状態を死へ
                enemyStatus.state = EnemyState.HitStop;
                IsDead = true;
                //  アニメーションを止める
                gameObject.GetComponent<Animator>().speed = 0.0f;

                gameObject.GetComponent<TrailRenderer>().enabled = true;

                //  死亡エフェクト
                GameObject de = Instantiate(deadHitEffect);
                de.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);

                //  回転のみ制限
                rd.constraints = RigidbodyConstraints.FreezeRotation;

                //  ぶっ飛ばす方向を設定
                vel = player.transform.forward * 30.0f;
            }
            else
            {
                //  攻撃中ならキャンセル
                if (enemyStatus.state == EnemyState.Attack) enemyStatus.state = EnemyState.Move;
            }
        }

        //  プレイヤーへの攻撃判定
        if (enemyStatus.state == EnemyState.Attack &&
            other.gameObject.CompareTag("Player") &&
            !attacked &&
            !playerController.Muteki())
        {
            //  攻撃分のダメージ
            playerController.Damaged(enemyStatus.power);
            //  攻撃した
            attacked = true;

            //  エフェクトを出す
            GameObject he = Instantiate(hitEffect);
            he.transform.position = player.transform.position + new Vector3(0.0f, 1.0f, 0.0f);

            audioSource.Play();
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        //  生成後のステージに着地
        if(enemyStatus.state == EnemyState.Create &&
            collision.gameObject.CompareTag("Floor"))
        {
            //  移動状態
            enemyStatus.state = EnemyState.Move;
            //  Y座標とX・Z回転をフリーズ
            rd.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
        }

        if(enemyStatus.state == EnemyState.Blow && 
            collision.gameObject.CompareTag("Stage"))
        {
            //  完全な死亡状態
            enemyStatus.state = EnemyState.Create;

            //  アニメーションを進める
            gameObject.GetComponent<Animator>().speed = 1.0f;
            //  死亡アニメーションの再生
            gameObject.GetComponent<Animator>().SetTrigger("Dead");
            //  死亡エフェクト
            GameObject de = Instantiate(deadEffect);
            de.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);
            //  制限
            rd.constraints = RigidbodyConstraints.FreezeAll;
        }
    }

    //  死亡アニメーションの終了
    void Dead()
    {
        enemyStatus.state = EnemyState.Dead;
    }
    //  攻撃アニメーションの終了
    void AttackAnimFinish()
    {
        enemyStatus.state = EnemyState.Move;
        attacked = false;
    }

    //  敵の状態を渡す
    public EnemyState GetEnemyState()
    {
        return enemyStatus.state;
    }

    public EnemyKind GetEnemyKind()
    {
        return enemyStatus.kind;
    }

    private void GaugeReduction(float reducationValue, float time = 1f)
    {
        var valueFrom = (float)enemyStatus.hp / (float)MaxHP;
        var valueTo = ((float)enemyStatus.hp - reducationValue) / (float)MaxHP;

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
