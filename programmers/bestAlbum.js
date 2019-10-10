function solution(genres, plays) {
    const set = new Set(genres);
    const obj = {};
    
    set.forEach(v => obj[v] = [0]);
    genres.forEach((v, i) => {
        obj[v][0] += plays[i];
        obj[v].push([plays[i], i]);
    });
    
    const newObj = Object.values(obj).sort((a, b) => a[0] < b[0] ? 1 : -1);
    newObj.filter(v => v.splice(0, 1));
    newObj.map(v => v.sort((a, b) => a[0] < b[0] ? 1 : -1).splice(2));
    
    return newObj.reduce((prev, cur) => prev.concat(cur), []).map(v => v[1]);
}