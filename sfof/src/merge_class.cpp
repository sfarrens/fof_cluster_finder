/*Class for merge clusters*/

#include "merge_class.hpp"

void Merge::join_uf(std::vector<Cluster> &clusters){
    // Create UnionFind groups.
    for(int i = 0; i < clusters.size(); i++)
        for(int j = 1; j< clusters[i].mem.size(); j++)
            clusters[i].mem[j]->uf.join(&clusters[i].mem[0]->uf);
}

void Merge::rearrange_clusters(std::vector<Galaxy>& gals, 
			       std::vector<Cluster>& clus_vec){
    // Create cluster instances using UnionFind data.
    typedef std::vector<Galaxy>::iterator gal_it;
    typedef std::map<UnionFind*, Cluster>::iterator map_it;
    std::map<UnionFind*, Cluster> m;
    for(gal_it it = gals.begin(); it != gals.end(); ++it){
        if(it->uf.is_singleton())
            continue;
        m[it->uf.find()].add_gal(&*it);
    }
    clus_vec.clear();
    clus_vec.reserve(m.size());
    unsigned long long i = 0;
    for(map_it it = m.begin(); it != m.end(); ++it){
        it->second.num = i;
        clus_vec.push_back(std::move(it->second));
        ++i;
    }
}

void Merge::rearrange_clusters(std::map<unsigned long, Galaxy>& gals, 
			       std::vector<Cluster>& clus_vec){
    // Create cluster instances using UnionFind data.
    typedef std::map<unsigned long, Galaxy>::iterator gal_it;
    typedef std::map<UnionFind*, Cluster>::iterator map_it;
    std::map<UnionFind*, Cluster> m;
    for(gal_it it = gals.begin(); it != gals.end(); ++it){
        if(it->second.uf.is_singleton())
            continue;
        m[it->second.uf.find()].add_gal(&it->second);
    }
    clus_vec.clear();
    clus_vec.reserve(m.size());
    unsigned long long i = 0;
    for(map_it it = m.begin(); it != m.end(); ++it){
        it->second.num = i;
        clus_vec.push_back(std::move(it->second));
        ++i;
    }
}
