﻿//     ----------     ----------     ----------     ----------     ----------
//
//                              AsLib - AsProject Library
//
//                    Created by Gaccho (wanotaitei@gmail.com)
//
//     ----------     ----------     ----------     ----------     ----------


namespace AsLib
{
	std::vector<size_t> vector2ToVector1(const std::vector<std::vector<size_t>>& map_) {
		static thread_local std::vector<size_t> vmap;
		const size_t i_max = map_.size();
		const size_t j_max = map_.data()->size();
		vmap.resize(i_max*j_max);
		for (size_t i = 0, k = 0; i < i_max; ++i) {
			for (size_t j = 0; j < j_max; ++j, ++k) {
				vmap[k] = map_[i][j];
			}
		}
		return vmap;
	}

	void mazeDig(std::vector<std::vector<size_t>>& map, size_t x, size_t y, const size_t aslib_maze_wall, const size_t aslib_maze_empty)
	{
		int32_t dx = 0;
		int32_t dy = 0;
		size_t r = size_t(asRand32());
		size_t c = 0;
		while (c < 4) {
			switch ((r + c) % 4)
			{
			case 0:
				dx = 0;
				dy = -1;
				break;
			case 1:
				dx = -1;
				dy = 0;
				break;
			case 2:
				dx = 0;
				dy = 1;
				break;
			case 3:
				dx = 1;
				dy = 0;
				break;
			}
			if (x + dx * 2 <= 0 || y + dy * 2 <= 0 || x + dx * 2 >= map.size() - 1 || y + dy * 2 >= map.data()->size() - 1 || map[x + dx * 2][y + dy * 2] == aslib_maze_empty) {
				++c;
			}
			else if (map[x + dx * 2][y + dy * 2] == aslib_maze_wall) {
				map[x + dx][y + dy] = aslib_maze_empty;
				map[x + dx * 2][y + dy * 2] = aslib_maze_empty;
				x += dx * 2;
				y += dy * 2;
				c = 0;
				r = size_t(asRand32());
			}
		}
		return;
	}
	void mazeRoot(std::vector<std::vector<size_t>>& map, const size_t x, const size_t y, const size_t aslib_maze_empty)
	{
		static size_t b = 0;
		map[x][y] = 2;
		if (x == map.size() - 2 && y == map.data()->size() - 2) b = 1;
		//上
		if (b != 1 && map[x][y - 1] == 0) mazeRoot(map, x, y - 1, aslib_maze_empty);
		//下
		if (b != 1 && map[x][y + 1] == 0) mazeRoot(map, x, y + 1, aslib_maze_empty);
		//左
		if (b != 1 && map[x - 1][y] == 0) mazeRoot(map, x - 1, y, aslib_maze_empty);
		//右
		if (b != 1 && map[x + 1][y] == 0) mazeRoot(map, x + 1, y, aslib_maze_empty);

		if (b != 1) map[x][y] = aslib_maze_empty;
		return;
	}
	//出力
	void mazeOutput(const std::vector<std::vector<size_t>>& map, const size_t aslib_maze_wall, const size_t aslib_maze_empty)
	{
		const size_t i_max = map.size();
		const size_t j_max = map.data()->size();
		for (size_t i = 0; i < i_max; ++i) {
			for (size_t j = 0; j < j_max; ++j) {
				if (map[i][j] == aslib_maze_empty)std::cout << u8"　";
				else if (map[i][j] == aslib_maze_wall)std::cout << u8"■";
				else if (map[i][j] == 2)std::cout << u8"・";
			}
			std::cout << std::endl;
		}
	}
	//迷路生成
	void mazeMake(std::vector<std::vector<size_t>>& map, const size_t aslib_maze_wall, const size_t aslib_maze_empty)
	{
		map[1][1] = aslib_maze_empty;

		size_t a = 0;
		size_t ii = 0;
		std::unique_ptr<size_t[]> X(new size_t[map.size()*map.data()->size()]);
		std::unique_ptr<size_t[]> Y(new size_t[map.size()*map.data()->size()]);
		while (true)
		{
			ii = 0;
			for (size_t y = 1; y < map.data()->size() - 1; y += 2) {
				for (size_t x = 1; x < map.size() - 1; x += 2) {
					if (map[x][y] != aslib_maze_empty) continue;
					if ((x >= 2 && map[x - 2][y] == aslib_maze_wall) || (y >= 2 && map[x][y - 2] == aslib_maze_wall)) {
						X[ii] = x;
						Y[ii] = y;
						++ii;
					}
					else if ((y == map.data()->size() - 2) && (x == map.size() - 2)) break;
					else if ((x + 2 < map.size() && map[x + 2][y] == aslib_maze_wall) || (y + 2 < map.data()->size() && map[x][y + 2] == aslib_maze_wall)) {
						X[ii] = x;
						Y[ii] = y;
						++ii;
					}
				}
			}
			if (ii == 0) break;
			else {
				a = size_t(asRand32()) % ii;
				mazeDig(map, X[a], Y[a], aslib_maze_wall, aslib_maze_empty);
			}
		}
		return;
	}

	std::vector<std::vector<size_t>> asMazeMapMake(const size_t size_x, const size_t size_y, const size_t aslib_maze_wall = 1, const size_t aslib_maze_empty = 0)
	{
		const size_t size_x_2 = (size_x % 2 == 1) ? size_x : size_x - 1;
		const size_t size_y_2 = (size_y % 2 == 1) ? size_y : size_y - 1;

		//迷路マップ
		static thread_local std::vector<std::vector<size_t>> map;
		map = std::vector<std::vector<size_t>>(size_x_2, std::vector<size_t>(size_y_2, aslib_maze_wall));

		//迷路を生成
		mazeMake(map, aslib_maze_wall, aslib_maze_empty);
		return map;
	}

	std::vector<std::vector<size_t>> asMazeMapDefault(const size_t size_x, const size_t size_y, const size_t aslib_maze_wall = 1, const size_t aslib_maze_empty = 0)
	{
		const size_t size_x_2 = (size_x % 2 == 1) ? size_x : size_x - 1;
		const size_t size_y_2 = (size_y % 2 == 1) ? size_y : size_y - 1;

		//迷路マップ
		static thread_local std::vector<std::vector<size_t>> map;
		map = std::vector<std::vector<size_t>>(size_x_2, std::vector<size_t>(size_y_2, aslib_maze_wall));
		//迷路を生成
		mazeMake(map, aslib_maze_wall, aslib_maze_empty);
		//経路探索
		mazeRoot(map, 1, 1, aslib_maze_empty);
		//入り口と出口追加
		map[1][0] = 2;
		map[size_x - 2][size_y - 1] = 2;
		//出力
		mazeOutput(map, aslib_maze_wall, aslib_maze_empty);
		return map;
	}


	//チャンク生成
	void asWorldMapMake(const size_t x_, const size_t y_, const size_t size_, const uint32_t t1_, const uint32_t t2_, const uint32_t t3_, const uint32_t t4_, uint32_t map_[17][17])
	{
		//再起の終了処理
		if (size_ == 0) return;
		//頂点の高さを決める
		const uint32_t mapPlus = ((t1_ + t2_ + t3_ + t4_) >> 2) + asRand(size_);
		map_[x_][y_] = (mapPlus >= 255) ? 255 : mapPlus;
		//四角形の2点同士の中点の高さを決定
		const uint32_t s1 = ((t1_ + t2_) >> 1);
		const uint32_t s2 = ((t1_ + t3_) >> 1);
		const uint32_t s3 = ((t2_ + t4_) >> 1);
		const uint32_t s4 = ((t3_ + t4_) >> 1);
		//4つの地点の座標を決める
		map_[x_ + size_][y_] = s3;
		map_[x_ - size_][y_] = s2;
		map_[x_][y_ + size_] = s4;
		map_[x_][y_ - size_] = s1;
		//分割サイズを半分にする
		const size_t size = size_ >> 1;
		//4つに分割
		asWorldMapMake(x_ - size, y_ - size, size, t1_, s1, s2, map_[x_][y_], map_);
		asWorldMapMake(x_ + size, y_ - size, size, s1, t2_, map_[x_][y_], s3, map_);
		asWorldMapMake(x_ - size, y_ + size, size, s2, map_[x_][y_], t3_, s4, map_);
		asWorldMapMake(x_ + size, y_ + size, size, map_[x_][y_], s3, s4, t4_, map_);
	}

	//チャンク生成の呼び出し
	inline void asWorldMapSimple(uint32_t map_[17][17])
	{
		//チャンク生成を実行
		asWorldMapMake(8, 8, 8, map_[0][0], map_[16][0], map_[0][16], map_[16][16], map_);
	}

	constexpr size_t aslib_world_make_seed1 = 0x3220;
	constexpr size_t aslib_world_make_seed2 = 0x292;

	//ワールドマップ生成
	void asWorldMake(std::vector<std::vector<uint32_t>>& world_map, size_t seed_ = 0)
	{
		if (seed_ == 0) seed_ = asRand(65535);
		static uint32_t map_[17][17]{};
		
		//横画面サイズ
		const size_t map_x = world_map.size();
		//縦画面サイズ
		const size_t map_y = world_map.front().size();

		const size_t chunk_x = (map_x >> 4);
		const size_t chunk_y = (map_y >> 4);

		for (size_t i = 0; i < chunk_x; ++i) {
			for (size_t j = 0; j < chunk_y; ++j) {

				//四角形の4点の高さを決定
				asSRand32(seed_ + i + (j * aslib_world_make_seed1) + ((i^j) * aslib_world_make_seed2));
				map_[0][0] = asRand(255);
				asSRand32(seed_ + ((i + 1) % chunk_x) + (j * aslib_world_make_seed1) + ((((i + 1) % chunk_x) ^ j) * aslib_world_make_seed2));
				map_[16][0] = asRand(255);
				asSRand32(seed_ + i + (((j + 1) % chunk_y) * aslib_world_make_seed1) + ((i ^ ((j + 1) % chunk_y)) * aslib_world_make_seed2));
				map_[0][16] = asRand(255);
				asSRand32(seed_ + ((i + 1) % chunk_x) + (((j + 1) % chunk_y) * aslib_world_make_seed1) + ((((i + 1) % chunk_x) ^ ((j + 1) % chunk_y)) * aslib_world_make_seed2));
				map_[16][16] = asRand(255);

				//チャンク生成
				asWorldMapSimple(map_);

				//生成したチャンクをワールドマップにコピペ
				for (size_t i2 = 0; i2 < 16; ++i2)
					for (size_t j2 = 0; j2 < 16; ++j2)
						world_map[(i << 4) + i2][(j << 4) + j2] = map_[i2][j2];

			}
		}
	}

	//世界をIDへ変換
	void asWorldMapSimplePaint(std::vector<size_t>& vec_, const size_t& x_, const size_t& y_, size_t& layer_, const size_t under_, const size_t sea_, const size_t green_, const size_t snow_, const size_t seed_ = 0) {
		std::vector<std::vector<uint32_t>> wmap(x_, std::vector<uint32_t>(y_, 255));
		//wmap = std::vector<std::vector<uint32_t>>(x_, std::vector<size_t>(y_, 255));
		//wmap.shrink_to_fit();

		asWorldMake(wmap, seed_);

		const size_t xy_ = x_ * y_;

		layer_ = 2;
		vec_.resize(xy_ * layer_);
		for (size_t i = 0; i < xy_; ++i) {
			vec_[i] = under_;
		}

		const size_t xyl_ = xy_ * layer_;
		for (size_t k = xy_, i = 0, j = 0; k < xyl_; ++k, ++j) {
			if (x_ <= j) {
				j = 0;
				++i;
			}
			//ワールドマップの線画
			if (wmap[i][j] <= 110 && wmap[i][j] > 50) continue;
			else if (wmap[i][j] < 15) {
				vec_[k] = snow_;
			}//内陸
			else if (wmap[i][j] <= 50) {
				vec_[k] = green_;
			}
			else {//海
				vec_[k] = sea_;
			}
		}
	}

}
