#define ASLIB_INCLUDE_DL
#include "AsLib.hpp"

int32_t asMain()
{
	//560, 700
	MainControl mc(u8"AsRPG", Pos2(1280,720));
	//キー
	AsKeyList kl;
	kl.addKeyOK().addKeyBack().addKeyCross().addKeyCrossW();

	//アイテムUIの画像
	Texture item_ui(u8"p/itemUI.png");
	Texture item_ui2(u8"p/itemUI2.png");
	//アイテムの画像
	Texture mushroom_te(u8"p/mushroom.png");
	Texture mushroom2_te(u8"p/mushroom2.png");

	//アイテムデータ
	std::vector<Item> item;
	item.emplace_back(Item(nullptr, u8"Empty"));
	item.emplace_back(Item(&mushroom_te, 10, u8"mushroom"));
	item.emplace_back(Item(&mushroom2_te, 5, u8"mushroom2"));

	//Texture key_cross_te(u8"p/key_cross.png", 3, 3);
	

	//属性数
	asSetAttribute(aslib_attribute_num);

	enum :size_t
	{
		aslib_item_empty,
		aslib_item_mushroom,
		aslib_item_mushroom2,
	};

	const PosA4 item_pos(Pos4F(0.45f, 0.7f, 0.55f, 0.9f).ratio());
	Font item_font(item_pos.w / 3, u8"Algerian");

	ShareItem share_item(8);
	share_item.push(0, aslib_item_mushroom, 5);
	share_item.push(1, aslib_item_mushroom2, 95);
	share_item.add(aslib_item_mushroom2, 25, item[aslib_item_mushroom2].stack_max);

	Inventory inv(item_ui, item_ui2, item_font, share_item, item_pos, 8, 0);

	constexpr Pos2 w_pos2(63,63);
	//モンスター
	AsTexture feri(u8"Picture/ikari.png", 6, 4);
	//マップテクスチャ
	AsTexture crystal1_te(u8"p/crystal1.png");
	AsTexture crystal2_te(u8"p/crystal2.png");
	AsTexture anime_te(u8"p/anime.png", 4);
	AsTexture sea1_te(u8"p/world_umi1.png", 4, 10);
	AsTexture sea2_te(u8"p/world_umi2.png", 4, 10);
	AsTexture sea3_te(u8"p/world_umi1.png", 4, 10);
	AsTexture sea4_te(u8"p/world_umi2.png", 4, 10);
	AsTexture mo1_te(u8"p/world_yama2.png", 2, 10);
	AsTexture mo2_te(u8"p/world_yama2-yuki.png", 2, 10);
	AsTexture underground_stairs_te(u8"p/undergroundStairs2.png");

	//マップ管理
	AsTextureMapArray main_map;
	main_map.push(nullptr);
	main_map.push(&crystal1_te, aslib_texture_map_field_type_empty);
	main_map.push(&crystal2_te, aslib_texture_map_field_type_empty);
	main_map.push(&anime_te, aslib_texture_map_field_type_empty);
	main_map.push(&sea1_te, aslib_texture_map_field_type_water);
	main_map.push(&sea2_te, aslib_texture_map_field_type_water);
	main_map.push(&sea3_te, aslib_texture_map_field_type_water);
	main_map.push(&sea4_te, aslib_texture_map_field_type_water);
	main_map.push(&mo1_te, aslib_texture_map_field_type_wall);
	main_map.push(&mo2_te, aslib_texture_map_field_type_wall);
	main_map.push(&underground_stairs_te, aslib_texture_map_field_type_empty);

	//フィールド属性
	AsAllAttribute att;
	att.push(aslib_default_field_attribute_empty);
	att.push(aslib_default_field_attribute_wall);
	att.push(aslib_default_field_attribute_water);
	att.push(aslib_default_field_attribute_keep_out);

	//マップ生成
	main_map.resizeMap(w_pos2);
	//main_map.worldMap(2, 4, 8, 9);
	//if (main_map.readCSV() == 1 && main_map.readBackupCSV() == 1) {
	//	main_map.resizeMap(w_pos2);
	//	main_map.setLayer(2, 1);
	//	main_map.randMap(1);
	//}
	//main_map.resizeMap(w_pos2);
	//main_map.putTexture();
	main_map.setLayer(2, 1);
	//main_map.randMap(1);
	//main_map.putMap(1, 1);
	main_map.mazeMap(4,0,1);

	constexpr PosA4F pl2(7.0f, 8.0f, 3.0f, 3.0f);
	constexpr PosA4F pl3(7.0f, 8.0f, 0.7f, 0.7f);

	constexpr PosA4F pl(1.0f, 1.0f, 1.0f, 1.0f);

	//イベント管理
	AsMapEventControl map_event(w_pos2,aslib_mob_walk_type_big, &feri, pl, aslib_map_event_type_mob);
	map_event.spawn().add(&feri, pl2);

	//マップ描画管理
	PosA4F map_p(0.0f, 0.0f, 5.0f, 10.0f);
	AsMapView map_view(map_p, 'y');
	map_view.setMap(w_pos2);
	
	constexpr size_t auto_save_timer = 60 * 22;
	size_t auto_save_counter = 0;
	constexpr size_t auto_backup_timer = 60 * 55;
	size_t auto_backup_counter = 0;

	map_event.setLandSpawn(main_map,att);

	//臨時タッチ
	Pos2 touch_event;

	while (asLoop())
	{
		//if (asTouch()) {
		//	touch_event = asTouchEndPos();
		//	if (touch_event.x < asWindowSize().x / 3) {
		//		if (touch_event.y < asWindowSize().y / 3) { asKeySet(aslib_key_w); asKeySet(aslib_key_a); }
		//		else if (touch_event.y < asWindowSize().y * 2 / 3) { asKeySet(aslib_key_a); }
		//		else { asKeySet(aslib_key_a); asKeySet(aslib_key_s); }
		//	}
		//	else if (touch_event.x < asWindowSize().x * 2 / 3) {
		//		if (touch_event.y < asWindowSize().y / 3) { asKeySet(aslib_key_w); }
		//		else if (touch_event.y < asWindowSize().y * 2 / 3) {}
		//		else { asKeySet(aslib_key_s); }
		//	}
		//	else {
		//		if (touch_event.y < asWindowSize().y / 3) { asKeySet(aslib_key_w); asKeySet(aslib_key_d); }
		//		else if (touch_event.y < asWindowSize().y * 2 / 3) { asKeySet(aslib_key_d); }
		//		else { asKeySet(aslib_key_d); asKeySet(aslib_key_s); }
		//	}
		//}

		//更新
		main_map.update();
		map_event.update(main_map, att, kl);
		//視点
		map_view.setMobView(map_event);
		//マップ描画
		map_view.draw(&main_map);
		//イベント描画
		map_view.draw(&map_event);

		map_event.talk(kl);

		//ランダムスポーン
		map_event.spawn(1).add(&feri, pl3);

		asTouchPinch(map_p, 10.0f);
		map_view.setLookSize(map_p, 'y');

		//++auto_save_counter;
		//if (auto_save_counter >= auto_save_timer) {
		//	auto_save_counter = 0;
		//	main_map.writeCSV();
		//}
		//++auto_backup_counter;
		//if (auto_backup_counter >= auto_backup_timer) {
		//	auto_backup_counter = 0;
		//	main_map.writeBackupCSV();
		//}
	}

	//main_map.writeCSV();

	//for (size_t i = 0; i < kl.ok.size(); ++i) if (kl.ok[i] < 256 && asKeyUp(kl.ok[i])) main_map.putBlock(4, pl, 1);
	//inv.selectAdd(mouseWheel()).draw(item).isSelectUp(asKeyL_Up()).isSelectDown(asKeyK_Up());

	return 0;
}