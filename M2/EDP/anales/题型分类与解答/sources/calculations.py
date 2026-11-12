"""Numerical verification for the printable classified EDP exercises.
Run from any directory: python3 calculations.py
Requires NumPy and SciPy. Existing TD4 verification is loaded read-only.
"""
from pathlib import Path
import importlib.util,json
import numpy as np
from scipy import stats
BASE=Path(__file__).resolve().parents[3]
spec=importlib.util.spec_from_file_location('td4_checks',BASE/'TD/td4_calculs.py')
td4=importlib.util.module_from_spec(spec);spec.loader.exec_module(td4)
def station(arrival,mu):
 a=np.array(arrival,dtype=float);m=np.array(mu,dtype=float)
 s_ms=(1000/m).tolist()
 w_ms=[float(1000*ai/(mi*(mi-ai))) if ai<mi else None for ai,mi in zip(a,m)]
 r_ms=[float(1000/(mi-ai)) if ai<mi else None for ai,mi in zip(a,m)]
 if np.any(a>=m): return dict(arrival=a.tolist(),mu=m.tolist(),rho=(a/m).tolist(),s_ms=s_ms,w_ms=w_ms,r_ms=r_ms,stable=False)
 return dict(arrival=a.tolist(),mu=m.tolist(),rho=(a/m).tolist(),s_ms=s_ms,w_ms=w_ms,r_ms=r_ms,stable=True)
def main():
 d={}
 d['amdahl']=[dict(P=p,S=1/(.04+.96/p),E=1/(.04*p+.96)) for p in 2**np.arange(2,8)]
 d['inverse_amdahl']=[dict(P=p,A=(p/sa-1)/(p-1),B=(p/sb-1)/(p-1)) for p,sa,sb in zip(range(2,9),[1.9,2.73,3.47,4.16,4.8,5.38,5.93],[1.94,2.72,3.34,3.82,4.2,4.49,4.72])]
 for key,times,ps in [('cray',[2.170,1.110,.754,.577,.312],[1,2,3,4,8]),('alliant',[66.1,34.8,24.9,20.5],[1,2,3,4])]:
  d[key]=[dict(P=p,T=t,S=times[0]/t,E=times[0]/t/p,e=(p*t/times[0]-1)/(p-1)) for p,t in zip(ps[1:],times[1:])]
 f=16.67e6;F=195578;Nh=f*1.08/10;Ns=f*13.6/6
 d['whetstone']=dict(MIPS_h=f/10/1e6,MIPS_s=f/6/1e6,N_h=Nh,N_s=Ns,Y_total=Ns/F,Y_emulation=1+(Ns-Nh)/F,MFLOPS=F/1.08/1e6)
 t=np.array([[33.4,28.8,28.3],[19.9,22.1,25.3],[6.5,5.3,4.7],[84.3,75.8,80.1],[101.1,99.4,70.2]])
 inst=np.array([1.45e10,7.97e9,3.11e9,3.77e10,4.56e10])
 mip=inst[:,None]/t/1e6;speed=t[:,2,None]/t
 d['benchmarks']=dict(mean_time=t.mean(0).tolist(),mips=mip.tolist(),mean_mips=mip.mean(0).tolist(),pooled_mips=(inst.sum()/t.sum(0)/1e6).tolist(),speedups=speed.tolist(),arithmetic_speed=speed.mean(0).tolist(),geometric_speed=stats.gmean(speed,axis=0).tolist(),suite_speed=(t[:,2].sum()/t.sum(0)).tolist())
 v=np.array([.3,.06,.206,.7992]);m=np.array([500,300,250,1000]);d['td3ex1']=station(800*v,m);d['td3ex1']['v']=v.tolist();d['td3ex1']['limit']=float(min(m/v));d['td3ex1']['long_ms']=sum(d['td3ex1']['r_ms'])
 d['td3ex2_I_exact']=station([1100,110,110,110],[10000,*([1/.00833]*3)])
 d['td3ex2_I_course']=station([1100,110,110,110],[10000,120,120,120])
 for key in ['td3ex2_I_exact','td3ex2_I_course']:
  r=d[key];r['W_all']=r['w_ms'][0]+.3*r['w_ms'][1];r['R_all']=r['r_ms'][0]+.3*r['r_ms'][1];r['W_io']=r['w_ms'][0]+r['w_ms'][1];r['R_io']=r['r_ms'][0]+r['r_ms'][1]
 d['td3ex2_II']=station([1100,26.4,165,138.6],[10000,1/.006,250,1/.00833])
 v23=np.array([.2,.8,.31*2/3,.31/3]);m23=np.array([1200,2500,1/.006,250]);d['exam2023queue']=station(1000*v23,m23);d['exam2023queue']['v']=v23.tolist();d['exam2023queue']['limit']=float(min(m23/v23));d['exam2023queue']['disk1_upgrade_stable']=float(1000*v23[2]);d['exam2023queue']['disk1_upgrade_W_le_S']=float(2000*v23[2])
 visits=np.array([1,.3,.94,.24]);mus=np.array([400,180,550,125])
 for key,mu in [('exam2025_initial',mus),('exam2025_upgrade1',mus*np.array([2,1,1,1])),('exam2025_upgrade2',mus*np.array([2,1,1,3]))]:
  r=station(320*visits,mu);r['W_contributions']=(visits*np.array(r['w_ms'])).tolist();r['S_contributions']=(visits*np.array(r['s_ms'])).tolist();r['W']=sum(r['W_contributions']);r['S']=sum(r['S_contributions']);r['R']=r['W']+r['S'];r['limit']=float(min(mu/visits));d[key]=r
 d['exam2025_local_first']=station(320*visits,mus*np.array([1,1,1,2])); q=d['exam2025_local_first']; q['W']=float(visits@np.array(q['w_ms'])); q['S']=float(visits@np.array(q['s_ms'])); q['R']=q['W']+q['S']
 d['exam2025_local_variant']=station(320*visits,mus*np.array([1,3,1,2])); q=d['exam2025_local_variant']; q['W']=float(visits@np.array(q['w_ms'])); q['S']=float(visits@np.array(q['s_ms'])); q['R']=q['W']+q['S']
 d['exam2025_speedup']= d['exam2025_initial']['R']/d['exam2025_upgrade2']['R'];d['exam2025_perf_cost']=d['exam2025_speedup']/1.75
 x=np.array([[.0972,.1382,.7966],[.0971,.1432,.5300],[.0969,.1382,.5152],[.1954,.1730,.6675],[.0974,.1383,.5298]])
 d['confidence']=dict(mean=x.mean(0).tolist(),sd=x.std(0,ddof=1).tolist())
 for c in [.90,.99]:
  half=stats.t.ppf((1+c)/2,4)*x.std(0,ddof=1)/np.sqrt(5)
  d['confidence'][str(c)]=np.column_stack([x.mean(0)-half,x.mean(0)+half]).tolist()
 for key,counts in [('dice',[9,4,18,15,6,8]),('generator',[100,96,98,85,105,93,97,125,107,94]),('cylinders',[29,19,18,25,17,10,15,11])]:
  result=stats.chisquare(counts);d[key]=dict(chi2=float(result.statistic),p=float(result.pvalue),df=len(counts)-1)
 d['cylinders']['p_one']=float(td4.discrete_uniform_ks_exact_p([29,19,18,25,17,10,15,11]));d['cylinders']['p_two']=float(td4.discrete_uniform_ks_exact_p([29,19,18,25,17,10,15,11],True))
 y=np.sort([.12,.45,.67,.23,.89,.34,.56,.78,.01,.99,.41,.62,.15,.73,.27,.51,.84,.39,.60,.95]);n=len(y)
 dp=np.arange(1,n+1)/n-y;dm=y-np.arange(n)/n
 counts=np.histogram(y,bins=[0,.2,.4,.6,.8,1])[0];ks=stats.kstest(y,'uniform',method='exact');ch=stats.chisquare(counts)
 d['exam2025uniform']=dict(sorted=y.tolist(),dp=dp.tolist(),dm=dm.tolist(),Dplus=float(max(dp)),Dminus=float(max(dm)),D=float(ks.statistic),p_ks=float(ks.pvalue),critical=float(stats.kstwo.ppf(.95,n)),counts=counts.tolist(),chi2=float(ch.statistic),p_chi2=float(ch.pvalue),critical_chi2=float(stats.chi2.ppf(.95,4)),p_chi2_exact=1-__import__('math').factorial(20)/(__import__('math').factorial(4)**5*5**20))
 d['generator_recomputed_hist']=[];x0=1;xs=[]
 for i in range(1000):x0=(125*x0+1)%4096;xs.append(x0/4096)
 d['generator_recomputed_hist']=np.histogram(xs,bins=np.linspace(0,1,11))[0].tolist()
 assert np.isclose(d['exam2025_initial']['W_contributions'][0],10)
 assert np.argmax(d['exam2025_initial']['W_contributions'])==0
 assert np.argmax(d['exam2025_upgrade1']['S_contributions'])==3
 assert d['exam2025uniform']['counts']==[3,4,4,5,4]
 out=Path(__file__).with_name('verified_results.json');out.write_text(json.dumps(d,ensure_ascii=False,indent=2,default=lambda x:int(x)))
 print(json.dumps(d,ensure_ascii=False,indent=2,default=lambda x:int(x)))
if __name__=='__main__':main()
