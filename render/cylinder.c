#include "../minirt.h"

double    get_cy_test_condition( double a, double b, double c, t_cylinder obj, bool *flag, t_ray ray)
{
    double    d;
    double harf_h;


    d = b * b - 4 * a * c;
    harf_h = obj.height/2;
    // if(d == 0){
    //     return ((-b - sqrt(d)) / (2*a));
    // }
    // else if (d > 0){
    //     double t1 = (-b - sqrt(d)) / (2*a);
    //     double t2 = (-b + sqrt(d)) / (2*a);
    //     // カメラに近い方の交点を選択
    //     if (t1 > 0 && t1 < t2)
    //         return t1;
    //     if (t2 > 0)
    //         return t2;
    // }
    *flag = false;
    if (d == 0)
        return ((-b - sqrt(d)) / (2*a));
    else if (d > 0){
        double t1 = (-b - sqrt(d)) / (2*a);
        double t2 = (-b + sqrt(d)) / (2*a);

        t_vec inter_pos_1 = add_vec(ray.pos, mul_vec(ray.dir, t1));
        t_vec inter_pos_2 = add_vec(ray.pos, mul_vec(ray.dir, t2));

        double diff_t1 = obj.center_vec.y - inter_pos_1.y;
        double diff_t2 = obj.center_vec.y - inter_pos_2.y;

        if (-harf_h < diff_t1 && diff_t1 < harf_h && -harf_h < diff_t2 && diff_t2 < harf_h){
            if (t1 > 0 && t1 < t2)
            {
                return t1;
            }
            if (t2 > 0) {
                return t2;
            }
        }
        else if (-harf_h <= diff_t1 && diff_t1 <= harf_h){
            *flag = true;
            return t1;
        }
        else if (-harf_h <= diff_t2 && diff_t2 <= harf_h){
            *flag = true;
            return t2;
        }
    }
    return (-1);
}

//交点位置をえきさんして高さの範囲内にあるか見る


//円柱のオブジェクトとレイの交差判定をしてベクトル情報を返す
//	交点がある場合は描写に必要なベクトル情報を構造体で返す
// 1: t_minirt *world -> 全体の情報を持つ構造体
// 2: t_objects tmp_o_list -> オブジェクトリストのノード
// 3: t_ray ray -> 交差判定をするレイ
t_vec_info cy_intersecton(t_minirt *world, t_objects tmp_o_list, t_ray ray) {
    t_vec        pvc;
    t_cylinder    *cy_obj;
    bool flag;

    cy_obj = tmp_o_list.content;
    pvc = sub_vec(ray.pos, cy_obj->center_vec);
    double A;
    double B;
    double C;
    double r = cy_obj->diameter / 2;
    double harf_h = cy_obj->height / 2;
    // printf("harf-h  %f", harf_h);
    t_vec_info res;

    A = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
    B = 2 * (pvc.x * ray.dir.x + pvc.z * ray.dir.z);
    C = pvc.x * pvc.x + pvc.z * pvc.z - r * r;

    res.t = get_cy_test_condition(A, B, C, *cy_obj, &flag, ray);
    // Dが０以上なら交点を持つ、0以上かつy軸距離が[−ℎ2,ℎ2]の範囲内である場合のみ交点を持つ
    if (res.t > 0) {
        //交点位置
        res.inter_pos = add_vec(ray.pos, mul_vec(ray.dir, res.t));
        double diff = cy_obj->center_vec.y - res.inter_pos.y;
        // 交点位置から円柱の中心へのベクトルを計算
        t_vec inter_to_center = sub_vec(res.inter_pos, cy_obj->center_vec);

        // 円柱の軸に平行な成分を除外
        inter_to_center.y = 0;
        inter_to_center.x *= 2;
        inter_to_center.z *= 2;

        // 法線ベクトルを正規化
        res.normal = vec_normalize(inter_to_center);
        //flagがtrueなら円柱の内側なので逆ベクトルにする
        if(flag == true){
            res.normal = mul_vec(res.normal, -1);
        }

        res.light_dir = vec_normalize(sub_vec(world->light->pos_vec, res.inter_pos));
        res.color = cy_obj->color;
    }
    return (res);
}
